#include "IO.hpp"

#include "config/EngineState.hpp"
#include "ui/ui.hpp"
#include "world/WorldManager.hpp"
#include "resources/ResourceManager.hpp"
// #include "renderer/RenderingManager.hpp"

#include "LeveledRenderingManager.hpp"
#include "listeners/TopToolbarListener.hpp"
#include "listeners/OpenListener.hpp"

World *IO::world = 0;

void onLevelChange(StateChangeData data) {

    string lvl = *(string *) data.value;
    cout << "level changed to: " << lvl << endl;
    ResourceManager::getInstance()->setWD(EngineState::getInstance()->getString("engine_wd") + "/data");
    ResourceManager::getInstance()->setLevel(lvl);
    World *w = (World*) ResourceManager::getInstance()->get("level.xml", LEVEL);
    ResourceManager::getInstance()->resolveAllDependencies();
    WorldManager::getInstance()->setWorld(w);
    for (auto a : LeveledRenderingManager::getInstance()->getActions()) {
        a->setWorld(w);
    }

    vector<LoadedResource *> ts = ResourceManager::getInstance()->getByType(TEXTURE);

    size_t ts_size = ts.size();
    for (size_t i = 0; i < ts_size; i++) {

        if (ts[i]->object) {

            LeveledRenderingManager::getInstance()->getRenderer()
                    ->setupTexture((Ballistic::Types::Texture *) ts[i]->object);
        }
    }
    //    LeveledRenderingManager::getInstance()->setupTextures();
    IO::world = WorldManager::getInstance()->getCurrentWorld();
}

IO::IO() {
}

IO::~IO() {
}

void IO::initWindow() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    SDL_CreateWindowAndRenderer(800, 600,
            SDL_WINDOW_OPENGL, &IO::window, &IO::displayRenderer);
}

void IO::eventLoop() {
    SDL_Event event;
    UI *ui = UI::getInstance();
    EngineState::getInstance()->setString("current_level", "");
    EngineState::getInstance()->setStateHandler("current_level", onLevelChange);


    TopToolbarListener *ttl = new TopToolbarListener();
    new OpenListener();

    while (!EngineState::getInstance()->getBool("exit")) {
        while (SDL_PollEvent(& event)) {

            switch (event.type) {
                case SDL_QUIT:
                    EngineState::getInstance()->setBool("exit", true);
                    break;

                case SDL_MOUSEWHEEL:

                    IO::world->observer.translate(0, 0, event.wheel.y);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        EngineState::getInstance()->setBool("view_drag", true);
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        EngineState::getInstance()->setBool("view_drag", false);
                    }
                    break;

                case  SDL_MOUSEMOTION:
                    if(EngineState::getInstance()->getBool("view_drag")) {
                        IO::world->observer.rotate(event.motion.yrel, event.motion.xrel, 0);
                    }
                    break;
                    
                case SDL_KEYUP:
                    if (event.key.keysym.sym == 'o') {
                        EngineState::getInstance()->setString("current_level", "level2");
                    }
                    break;
            }



            UI::getInstance()->processSDLEvent(event);
        }
        LeveledRenderingManager::getInstance()->render();
    }
}