#ifndef SIGNALS_HPP
#define	SIGNALS_HPP

#include <Rocket/Core/EventListener.h>

class TopToolbarListener : public Rocket::Core::EventListener {
public:
    void ProcessEvent(Rocket::Core::Event& event);
};



#endif
