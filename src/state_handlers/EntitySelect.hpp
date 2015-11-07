#ifndef ENTITYSELECT_HPP
#define	ENTITYSELECT_HPP

#include "misc/StateHandler.hpp"
#include "listeners/EditorEventListener.hpp"

class EntitySelect : public StateHandler {
protected:
    EditorEventListener *listener;
    UIDocument *doc;
public:
    EntitySelect();
    virtual void after(StateChangeData data);
};

#endif	/* ENTITYSELECT_HPP */

