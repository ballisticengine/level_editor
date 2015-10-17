#ifndef COLORDECORATOR_HPP
#define	COLORDECORATOR_HPP

#include "renderer/RenderingActionDecorator.hpp"

class ColorDecorator : public RenderingActionDecorator{
public:
    virtual void before();
    virtual void after();


};

#endif	/* COLORDECORATOR_HPP */

