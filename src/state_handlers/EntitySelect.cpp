#include "EntitySelect.hpp"

#include <boost/lexical_cast.hpp>

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
            (Rocket::Controls::ElementFormControlInput*) doc->getElementById("entity_name"),
            *entity_type = (Rocket::Controls::ElementFormControlInput*) doc->getElementById("entity_type"),
            *x = (Rocket::Controls::ElementFormControlInput*) doc->getElementById("entity_x"),
            *y = (Rocket::Controls::ElementFormControlInput*) doc->getElementById("entity_x"),
            *z = (Rocket::Controls::ElementFormControlInput*) doc->getElementById("entity_x")
            ;
    
    Coords c = entity->getCoords();
    
    entity_name->SetValue(entity->name.c_str());
    entity_type->SetValue(entity->type.c_str());
//    x->setValue(boost::lexical_cast<std::string>(c.translation.x).c_str());
//    y->setValue(boost::lexical_cast<std::string>(c.translation.y).c_str());
//    z->setValue(boost::lexical_cast<std::string>(c.translation.z).c_str());
}