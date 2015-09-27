#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP

#include "renderer/RenderingManagerInterface.hpp"
#include "misc/singleton.hpp"

class LeveledRenderingManager : public RenderingManagerInterface, public Singleton<LeveledRenderingManager> {
    public:
        virtual void render();
};
#endif	

