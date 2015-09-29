#ifndef FILELISTENER_HPP
#define	FILELISTENER_HPP

#include <Rocket/Core/EventListener.h>

class FileListener : public Rocket::Core::EventListener {
protected:

public:
    FileListener();
    virtual ~FileListener();
    void ProcessEvent(Rocket::Core::Event& event);


};

#endif	

