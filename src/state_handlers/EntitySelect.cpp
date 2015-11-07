#include "EntitySelect.hpp"

#include "entities/ObjectEntity.hpp"
#include "listeners/ObjectSettingsHandler.hpp"
#include "ui/ui.hpp"

EntitySelect::EntitySelect() {
    listener = new ObjectSettingsHandler();
    doc = UI::getInstance()->addDocument("object_settings.rml", "object-settings");
}

void EntitySelect::after(StateChangeData data) {
    ObjectEntity *entity = (ObjectEntity *) data.value;
    cout << "EntitySelect " << entity->name << endl;
    UI::getInstance()->getDocument("object-settings")->show();
    Rocket::Controls::ElementFormControlInput *entity_name =
            (Rocket::Controls::ElementFormControlInput*) doc->getElementById("entity_name");
     entity_name->SetValue(entity->name.c_str());
}