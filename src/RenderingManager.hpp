#ifndef RENDERINGMANAGER_HPP
#define	RENDERINGMANAGER_HPP


#include "renderer/RenderingManagerEngine.hpp"
#include "misc/singleton.hpp"

class LeveledRenderingManager : public RenderingManagerEngine, public Singleton<LeveledRenderingManager> {
    public:
        virtual void render();
};
#endif	

