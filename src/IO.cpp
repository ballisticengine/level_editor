#include "IO.hpp"

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
    while(true) {
        
    }
}