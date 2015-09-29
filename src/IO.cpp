#include "IO.hpp"

#include "config/EngineState.hpp"
#include "ui/ui.hpp"

#include "RenderingManager.hpp"
#include "TopToolbarListener.hpp"


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
    ui->addDocument("top-toolbar.rml", "top-toolbar")->show();
    /*
      AddEventListener(const EMP::Core::String& event,
                      Rocket::Core::EventListener* listener,
                      bool in_capture_phase = false);
     */
    TopToolbarListener *ttl = new TopToolbarListener();
    ui->getDocument("top-toolbar")->getDocument()
    ->GetElementById("file")->AddEventListener("click",  ttl);
     ui->getDocument("top-toolbar")->getDocument()
    ->GetElementById("options")->AddEventListener("click",  ttl);
    while (!EngineState::getInstance()->getBool("exit")) {
        while (SDL_PollEvent(& event)) {

            if (event.type == SDL_QUIT) {
                EngineState::getInstance()->setBool("exit", true);
            }
            
            UI::getInstance()->processSDLEvent(event);
        }
        LeveledRenderingManager::getInstance()->render();
    }
}