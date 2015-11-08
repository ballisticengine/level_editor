#include "listeners/TopToolbarListener.hpp"

#include <iostream>
#include <Rocket/Core.h>

using namespace std;

#include "ui/ui.hpp"
#include "ui/UIDocument.hpp"

TopToolbarListener::TopToolbarListener() {

    UIDocument *doc = ui->addDocument("top-toolbar.rml", "top-toolbar");
    doc->show();

    Rocket::Core::ElementList elements;
    doc->getElements("li", elements);

    for (auto el : elements) {
        el->AddEventListener("click", this);
    }

    //    ui->getDocument("top-toolbar")->getDocument()
    //    ->GetElementById("file")->AddEventListener("click",  this);
    //     ui->getDocument("top-toolbar")->getDocument()
    //    ->GetElementById("options")->AddEventListener("click",  this);
}

void TopToolbarListener::ProcessEvent(Rocket::Core::Event& event) { 
//    UI *ui = UI::getInstance();
//    Rocket::Core::Element *el = ui->getDocument("top-toolbar")->getDocument()->GetElementById("file");
//
//    string id = string(event.GetTargetElement()->GetId().CString());
//    cout << id << endl;
//    if (id == "file" || id == "options" || id == "res") {
//        event.GetTargetElement()->SetClass("active", true);
//    }
//
//    if (id == "open") {
//        ui->getDocument("open-dialog")->show();
//    }
//
//    if (id == "save-as") {
//        ui->getDocument("save-dialog")->show();
//    }
}