#ifndef LEVELCHANGE_HPP
#define	LEVELCHANGE_HPP

#include "misc/StateHandler.hpp"

class LevelChange : public StateHandler {
public:
    virtual void before(StateChangeData data);
    virtual void after(StateChangeData data);

};

#endif	/* LEVELCHANGE_HPP */

