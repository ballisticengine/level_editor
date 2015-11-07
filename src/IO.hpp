#ifndef IO_HPP
#define	IO_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "io/SDLIOInterface.hpp"
#include "world/World.hpp"
#include "misc/singleton.hpp" 

class IO : public SDLIOInterface, public Singleton<IO> {
private:
    virtual void initWindow();
public:
    IO();
    virtual ~IO();
    virtual void eventLoop();
};

#endif	

