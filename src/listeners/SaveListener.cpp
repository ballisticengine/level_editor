#include "SaveListener.hpp"
#include "libload/LibLoad.hpp"
#include "resources/WorldLoader.hpp"
#include "world/WorldManager.hpp"
#include <boost/filesystem.hpp>

SaveListener::SaveListener() {
    Rocket::Core::ElementDocument *doc = ui->addDocument("save_dialog.rml", "save-dialog")->getDocument();

    doc->GetElementById("ok")->AddEventListener("click", this);
    doc->GetElementById("cancel")->AddEventListener("click", this);
}

void SaveListener::ProcessEvent(Rocket::Core::Event& event) {
    string id = string(event.GetTargetElement()->GetId().CString());

    WorldLoader *l = (WorldLoader *) LibLoad::getInstance()->getLoaderByExtension("xml", LEVEL);

    if (id == "ok") {
        Rocket::Controls::ElementFormControlInput *el = (Rocket::Controls::ElementFormControlInput*)
                ui->getDocument("save-dialog")->getElementById("save-level-name");

        cout << "Save into" << el->GetValue().CString() << endl;
        
        string save_path = EngineState::getInstance()->getString("engine_wd") + 
                "/data/levels/" + el->GetValue().CString();
        string save_fn =  save_path + "/level.xml";
        
        boost::filesystem::create_directories(save_path);
        
        l->save(WorldManager::getInstance()->getCurrentWorld(), save_fn);
        ui->getDocument("save-dialog")->hide();
    }

    if (id == "cancel") {
        ui->getDocument("save-dialog")->hide();
    }
}

