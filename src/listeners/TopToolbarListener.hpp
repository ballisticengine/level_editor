#ifndef SIGNALS_HPP
#define	SIGNALS_HPP

#include "listeners/EditorEventListener.hpp"

class TopToolbarListener : public EditorEventListener {
public:
    TopToolbarListener();
    void ProcessEvent(Rocket::Core::Event& event);
};



#endif
