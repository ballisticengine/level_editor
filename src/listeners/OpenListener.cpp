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

        cout << "ok" << endl;
       
       
    }

    if (id == "cancel") {
        cout << "cancel" << endl;
    }

    ui->getDocument("open-dialog")->hide();
}