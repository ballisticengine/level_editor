#ifndef SAVELISTENER_HPP
#define	SAVELISTENER_HPP

#include "listeners/EditorEventListener.hpp"

class SaveListener : public EditorEventListener {
public:
    SaveListener();
    void ProcessEvent(Rocket::Core::Event& event);

};

#endif	

