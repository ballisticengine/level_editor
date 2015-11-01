#ifndef OBJECTSETTINGSHANDLER_HPP
#define	OBJECTSETTINGSHANDLER_HPP

#include "listeners/EditorEventListener.hpp"

class ObjectSettingsHandler : public EditorEventListener {
protected:
    Rocket::Core::ElementDocument *doc;
public:
    ObjectSettingsHandler();
    void ProcessEvent(Rocket::Core::Event& event);
};

#endif	

