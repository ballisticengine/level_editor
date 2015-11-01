#include "SaveListener.hpp"

SaveListener::SaveListener() {
    Rocket::Core::ElementDocument *doc = ui->addDocument("save_dialog.rml", "save-dialog")->getDocument();

    doc->GetElementById("ok")->AddEventListener("click", this);
    doc->GetElementById("cancel")->AddEventListener("click", this);
}

void SaveListener::ProcessEvent(Rocket::Core::Event& event) {
    string id = string(event.GetTargetElement()->GetId().CString());

    if (id == "ok") {
        Rocket::Controls::ElementFormControlInput *el = (Rocket::Controls::ElementFormControlInput*)
                ui->getDocument("save-dialog")->getElementById("save-level-name");
        
        cout << "Save into" << el->GetValue().CString() << endl;
        ui->getDocument("save-dialog")->hide();
    }

    if (id == "cancel") {
        ui->getDocument("save-dialog")->hide();
    }
}

