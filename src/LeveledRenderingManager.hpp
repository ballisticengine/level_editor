#ifndef LEVELEDRENDERINGMANAGER_HPP
#define	LEVELEDRENDERINGMANAGER_HPP


#include "renderer/RenderingManagerInterface.hpp"
#include "renderer/RenderingManager.hpp"
#include "misc/singleton.hpp"

class LeveledRenderingManager : public RenderingManagerInterface, public Singleton<LeveledRenderingManager> {
    protected:
        RenderingManager *rm;
    public:
        LeveledRenderingManager();
        virtual void render();
};
#endif	

