#include <iostream>

using namespace std;


#include "config/EngineState.hpp"
#include "libload/LibLoad.hpp"
#include "renderer/RendererInterface.hpp"

#include "IO.hpp"
#include "RenderingManager.hpp"

int main() {
    cout << "Ballistic Engine Level Editor" << endl;
    LibLoad::getInstance()->setWD("../ballistic_engine/bin");
    LibLoad::getInstance()->discoverLoaders();
    LibLoad::getInstance()->registerModule("renderer2", "RendererOpenGL", "returnRenderer");
    
    RendererInterface *ri = (RendererInterface *) LibLoad::getInstance()->getModuleClass("renderer2");
    LeveledRenderingManager *rm = LeveledRenderingManager::getInstance();
    rm->setRenderer(ri);
    
    
    EngineState::getInstance()->setBool("exit", false);
    IO *io = IO::getInstance();
    io->init(io);
    io->eventLoop();
}
