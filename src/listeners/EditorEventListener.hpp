#ifndef EDITOREVENTLISTENER_HPP
#define	EDITOREVENTLISTENER_HPP

#include <Rocket/Core/EventListener.h>

#include "ui/ui.hpp"

class EditorEventListener : public Rocket::Core::EventListener {
protected:
    UI *ui;
    Rocket::Core::ElementDocument *doc;
public:
    EditorEventListener();
    virtual ~EditorEventListener();
};

#endif	

