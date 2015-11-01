#include "listeners/OpenListener.hpp"

OpenListener::OpenListener() {
    Rocket::Core::ElementDocument *doc = ui->addDocument("open_dialog.rml", "open-dialog")->getDocument();

    doc->GetElementById("ok")->AddEventListener("click", this);
    doc->GetElementById("cancel")->AddEventListener("click", this);
}

OpenListener::~OpenListener() {
}

void OpenListener::ProcessEvent(Rocket::Core::Event& event) {
    string id = string(event.GetTargetElement()->GetId().CString());

    if (id == "ok") {
        Rocket::Controls::ElementFormControlInput *el = (Rocket::Controls::ElementFormControlInput*)
                ui->getDocument("open-dialog")->getElementById("open-level-name");
        EngineState::getInstance()->setString("current_level", el->GetValue().CString());
        ui->getDocument("open-dialog")->hide();
    }

    if (id == "cancel") {
        cout << "cancel" << endl;
        ui->getDocument("open-dialog")->hide();
    }


}