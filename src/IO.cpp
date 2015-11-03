#include "IO.hpp"

#include <cmath>

#include "config/EngineState.hpp"
#include "ui/ui.hpp"
#include "world/WorldManager.hpp"
#include "resources/ResourceManager.hpp"
#include "libload/LibLoad.hpp"
// #include "renderer/RenderingManager.hpp"

#include "rendering/LeveledRenderingManager.hpp"
#include "listeners/TopToolbarListener.hpp"
#include "listeners/OpenListener.hpp"
#include "listeners/SaveListener.hpp"


#include "state_handlers/LevelChange.hpp"
#include "state_handlers/EntitySelect.hpp"



#define PI 3.14159265358979323846
#define DEG2RAD(DEG) ((DEG)*((PI)/(180.0)))


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
    
    
    EngineState::getInstance()->setStateHandler("current_level", new LevelChange());
    EngineState::getInstance()->setStateHandler("selected_entity", new EntitySelect());

    int mouse_x, mouse_y;
    TopToolbarListener *ttl = new TopToolbarListener();
    new OpenListener();
    new SaveListener();
    Vector3d rotation;
    e_loc lx, ly, lz;
    LeveledRenderingManager::getInstance()
            ->getRenderer()->addShader("light");
    WorldManager *wm = WorldManager::getInstance();
    while (!EngineState::getInstance()->getBool("exit")) {

        while (SDL_PollEvent(& event)) {

            switch (event.type) {
                case SDL_QUIT:
                    EngineState::getInstance()->setBool("exit", true);
                    break;

                case SDL_MOUSEWHEEL:

                    rotation = wm->getCurrentWorld()->observer.getCoords().rotation;
                    lx = sin(DEG2RAD(rotation.x)) * event.wheel.y;
                    ly = -sin(DEG2RAD(rotation.x)) * event.wheel.y;
                    lz = cos(DEG2RAD(rotation.y)) * event.wheel.y;


                    wm->getCurrentWorld()->observer.translate(lx, ly, lz);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        SDL_GetMouseState(&mouse_x, &mouse_y);
                        if (wm->getCurrentWorld()) {
                            RendererInterface *ri = LeveledRenderingManager::getInstance()->getRenderer();
                            ri->turnLights(false);
                            LeveledRenderingManager::getInstance()->renderColored();
                            ColorRGBA c = ri->readPixel(event.button.x, event.button.y);
                            //ri->turnLights(true);

                           EngineState::getInstance()->setPtr("selected_entity", 
                                   wm->getCurrentWorld()->findEntityByColor(c));
//                            if (EngineState::getInstance()->getPtr("selected_entity")) {
//                                cout << "Name: " << wm->getCurrentWorld()->findEntityByColor(c)->name << endl;
//                            }
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
                            wm->getCurrentWorld()->observer.rotate(event.motion.yrel, event.motion.xrel, 0);
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