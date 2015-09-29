#include "TopToolbarListener.hpp"

#include <iostream>

using namespace std;

#include "ui/ui.hpp"

void TopToolbarListener::ProcessEvent(Rocket::Core::Event& event) {
    UI *ui = UI::getInstance(); 
    Rocket::Core::Element *el = ui->getDocument("top-toolbar")->getDocument()->GetElementById("file");
    
    string id = string(event.GetTargetElement()->GetId().CString());
    cout << id << endl;
    if (id == "file" || id == "options") {
        event.GetTargetElement()->SetClass("active", true);
    }
}