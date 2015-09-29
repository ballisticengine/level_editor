#include "TopToolbarListener.hpp"

#include <iostream>

using namespace std;

#include "ui/ui.hpp"

TopToolbarListener::TopToolbarListener() {
    ui->addDocument("top-toolbar.rml", "top-toolbar")->show();
    ui->getDocument("top-toolbar")->getDocument()
    ->GetElementById("file")->AddEventListener("click",  this);
     ui->getDocument("top-toolbar")->getDocument()
    ->GetElementById("options")->AddEventListener("click",  this);
}

void TopToolbarListener::ProcessEvent(Rocket::Core::Event& event) {
    UI *ui = UI::getInstance(); 
    Rocket::Core::Element *el = ui->getDocument("top-toolbar")->getDocument()->GetElementById("file");
    
    string id = string(event.GetTargetElement()->GetId().CString());
    cout << id << endl;
    if (id == "file" || id == "options") {
        event.GetTargetElement()->SetClass("active", true);
    }
}