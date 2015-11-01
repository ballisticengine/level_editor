#include "IO.hpp"

#include <cmath>

#include "config/EngineState.hpp"
#include "ui/ui.hpp"
#include "world/WorldManager.hpp"
#include "resources/ResourceManager.hpp"
// #include "renderer/RenderingManager.hpp"

#include "rendering/LeveledRenderingManager.hpp"
#include "listeners/TopToolbarListener.hpp"
#include "listeners/OpenListener.hpp"
#include "listeners/SaveListener.hpp"
#include "libload/LibLoad.hpp"


World *IO::world = 0;


#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))

void onLevelChange(StateChangeData data) {

    Loader *l = (Loader *) LibLoad::getInstance()->getLoaderByExtension("xml", LEVEL);
    //l->setBool("triangles", true);
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
            LeveledRenderingManager::getInstance()
                    ->getRenderer()
                    ->setupTexture((Ballistic::Types::Texture *) ts[i]->object);
        }
    }

    IO::world = WorldManager::getInstance()->getCurrentWorld();
    IO::world->colorize();
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
    EngineState::getInstance()->setString("mode", "normal");
    EngineState::getInstance()->setStateHandler("current_level", onLevelChange);

    int mouse_x, mouse_y;
    TopToolbarListener *ttl = new TopToolbarListener();
    new OpenListener();
    new SaveListener();
    Vector3d rotation;
    e_loc lx, ly, lz;
    LeveledRenderingManager::getInstance()
            ->getRenderer()->addShader("light");
    while (!EngineState::getInstance()->getBool("exit")) {

        while (SDL_PollEvent(& event)) {

            switch (event.type) {
                case SDL_QUIT:
                    EngineState::getInstance()->setBool("exit", true);
                    break;

                case SDL_MOUSEWHEEL:

                    rotation = IO::world->observer.getCoords().rotation;
                    lx = sin(DEG2RAD(rotation.x)) * event.wheel.y;
                    ly = -sin(DEG2RAD(rotation.x)) * event.wheel.y;
                    lz = cos(DEG2RAD(rotation.y)) * event.wheel.y;


                    IO::world->observer.translate(lx, ly, lz);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        if (IO::world) {
                            RendererInterface *ri = LeveledRenderingManager::getInstance()->getRenderer();
                            ri->turnLights(false);
                            LeveledRenderingManager::getInstance()->renderColored();
                            ColorRGBA c = ri->readPixel(event.button.x, event.button.y);
                            //ri->turnLights(true);

                           EngineState::getInstance()->setPtr("selected_entity",IO::world->findEntityByColor(c));
                            if (EngineState::getInstance()->getPtr("selected_entity")) {
                               // cout << "Name: " << IO::selected_entity->name << endl;
                            }
                        }
                    }

                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        EngineState::getInstance()->setBool("view_drag", true);
                    }
                    break;

                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_RIGHT) {
                        EngineState::getInstance()->setBool("view_drag", false);
                    }
                    break;

                case SDL_MOUSEMOTION:
                    if (EngineState::getInstance()->getString("mode") == "normal") {
                        if (EngineState::getInstance()->getBool("view_drag")) {
                            IO::world->observer.rotate(event.motion.yrel, event.motion.xrel, 0);
                        }
                    }

                    if (EngineState::getInstance()->getString("mode") == "translate") {
                        SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
                        ((ObjectEntity *)EngineState::getInstance()->getPtr("selected_entity"))->translate(mouse_x / 10, mouse_y / 10, 0);
                    }

                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
//                        case 'o':
//                            EngineState::getInstance()->setString("current_level", "level2");
//                            break;
                        case 't':
                            if (EngineState::getInstance()->getPtr("selected_entity")) {
                                EngineState::getInstance()->setString("mode", "translate");
                            }
                            break;
                        case 'n':
                            EngineState::getInstance()->setString("mode", "normal");
                            break;
                    }



                    break;
            }

            UI::getInstance()->processSDLEvent(event);
        }
        LeveledRenderingManager::getInstance()->render();

    }
}