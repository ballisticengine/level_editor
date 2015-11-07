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
    EngineState *es = EngineState::getInstance();
    es->setString("current_level", "");
    es->setString("transform_mode", "translate");
    es->setNumber("move_multipler", 10);
    es->setStateHandler("current_level", new LevelChange());
    es->setStateHandler("selected_entity", new EntitySelect());

    int mouse_x, mouse_y;
    TopToolbarListener *ttl = new TopToolbarListener();
    new OpenListener();
    new SaveListener();
    Vector3d rotation;
    e_loc lx, ly, lz;
    LeveledRenderingManager::getInstance()
            ->getRenderer()->addShader("light");
    WorldManager *wm = WorldManager::getInstance();
    double m, tx, ty, tz;
    while (!EngineState::getInstance()->getBool("exit")) {

        while (SDL_PollEvent(& event)) {

            switch (event.type) {
                case SDL_QUIT:
                    EngineState::getInstance()->setBool("exit", true);
                    break;

                case SDL_MOUSEWHEEL:

                    rotation = wm->getCurrentWorld()->observer.getCoords().rotation;
                    m = es->getNumber("move_multipler");
                    lx = -sin(DEG2RAD(rotation.y)) * event.wheel.y*m;
                    ly = sin(DEG2RAD(rotation.x)) * event.wheel.y*m;
                    lz = cos(DEG2RAD(rotation.y)) * event.wheel.y*m;


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

                            EngineState::getInstance()->setPtr("selected_entity",
                                    wm->getCurrentWorld()->findEntityByColor(c));
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

                    if (EngineState::getInstance()->getBool("view_drag")) {
                        wm->getCurrentWorld()->observer.rotate(event.motion.yrel, event.motion.xrel, 0);
                    }

                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            ((ObjectEntity *) es->getPtr("selected_entity"))->translate(1, 0, 0);
                            break;
                        case SDLK_RIGHT:
                            ((ObjectEntity *) es->getPtr("selected_entity"))->translate(-1, 0, 0);
                            break;
                        case SDLK_UP:
                            ((ObjectEntity *) es->getPtr("selected_entity"))->translate(0, 0, 1);
                            break;
                        case SDLK_DOWN:
                            ((ObjectEntity *) es->getPtr("selected_entity"))->translate(0, 0, -1);
                            break;
                        case ',':
                            ((ObjectEntity *) es->getPtr("selected_entity"))->translate(0, 1, 0);
                            break;

                        case '.':
                            ((ObjectEntity *) es->getPtr("selected_entity"))->translate(0, -1, 0);
                            break;
                    };
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                            
                        case 't':
                            EngineState::getInstance()->setString("transform_mode", "translate");
                            break;
                            
                        case 'r':
                            EngineState::getInstance()->setString("transform_mode", "rotate");
                            break;

                    }



                    break;
            }

            UI::getInstance()->processSDLEvent(event);
        }
        LeveledRenderingManager::getInstance()->render();

    }
}