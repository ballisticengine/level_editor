#ifndef OPENLISTENER_HPP
#define	OPENLISTENER_HPP

#include "listeners/EditorEventListener.hpp"

class OpenListener : public EditorEventListener {
protected:

public:
    OpenListener();
    virtual ~OpenListener();
    void ProcessEvent(Rocket::Core::Event& event);


};

#endif	

