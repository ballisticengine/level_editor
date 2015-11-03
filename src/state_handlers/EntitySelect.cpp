#include "EntitySelect.hpp"

#include "entities/ObjectEntity.hpp"
#include "listeners/ObjectSettingsHandler.hpp"


EntitySelect::EntitySelect() {
    listener = new ObjectSettingsHandler();
}

void EntitySelect::before(StateChangeData data) {
    
}

void EntitySelect::after(StateChangeData data) {
    ObjectEntity *entity = (ObjectEntity *) data.value;
    cout << "EntitySelect " << entity->name << endl;
}