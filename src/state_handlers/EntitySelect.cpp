#include "EntitySelect.hpp"

#include "listeners/ObjectSettingsHandler.hpp"


EntitySelect::EntitySelect() {
    listener = new ObjectSettingsHandler();
}

void EntitySelect::before(StateChangeData data) {
    
}

void EntitySelect::after(StateChangeData data) {
    cout << "EntitySelect" << endl;
}