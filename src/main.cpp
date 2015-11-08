#include <iostream>

using namespace std;


#include "config/EngineState.hpp"
#include "libload/LibLoad.hpp"
#include "renderer/RendererInterface.hpp"
#include "ui/librocket_interfaces/RendererInterfaceSDL2.hpp"
#include "ui/librocket_interfaces/ShellFileInterface.hpp"
#include "ui/librocket_interfaces/SystemInterfaceSDL2.hpp"
#include "ui/ui.hpp"
#include "python/scripting.hpp"

#include "IO.hpp"
#include "rendering/LeveledRenderingManager.hpp"

int main() {
    cout << "Ballistic Engine Level Editor" << endl;
    
    PyScripting::getInstance()->init();
    PyScripting::getInstance()->loadManipulator("./data/common/scripts", "UI"); 
      
    EngineState::getInstance()->setBool("exit", false);
    EngineState::getInstance()->setString("engine_wd", "../ballistic_engine");
    EngineState::getInstance()->setBool("lighting", true);

    IO *io = IO::getInstance();
    io->init(io);

    LibLoad::getInstance()->setWD(EngineState::getInstance()->getString("engine_wd") + "/bin");
    LibLoad::getInstance()->discoverLoaders();
    LibLoad::getInstance()->registerModule("renderer2", "RendererOpenGL", "returnRenderer");

    string ui_dir = "./data/ui/";

    RendererInterface *ri = (RendererInterface *) LibLoad::getInstance()->getModuleClass("renderer2");
    ri->init(800, 600, IO::getInstance());
    LeveledRenderingManager *rm = LeveledRenderingManager::getInstance();

    rm->setRenderer(ri);

    rm->setFlush(IO::flush);
    Rocket::Core::RenderInterface *ui_renderer = ri->getUiRenderer();
    RocketSDL2SystemInterface *system_interface = new RocketSDL2SystemInterface();
    Rocket::Core::FileInterface *file_interface = new ShellFileInterface(ui_dir.c_str());

    UI *ui = UI::getInstance();

    if (!ui->init(system_interface, ui_renderer, file_interface, rm->getRenderer())) {
        cout << "UI loading error" << endl;
    } else {
        cout << "UI loaded!" << endl;
    }

    
    io->eventLoop();
    ui->cleanup();
    PyScripting::getInstance()->cleanup();
    
}
