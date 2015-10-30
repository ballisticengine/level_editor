#ifndef LEVELEDRENDERINGMANAGER_HPP
#define	LEVELEDRENDERINGMANAGER_HPP

#include <vector>

using namespace std;

#include "renderer/RenderingManagerInterface.hpp"
#include "renderer/RenderingManager.hpp"
#include "renderer/RenderingAction.hpp"
#include "misc/singleton.hpp"

class LeveledRenderingManager : public RenderingManagerInterface, public Singleton<LeveledRenderingManager> {
    protected:
        RenderingAction *ui_action;
        vector<RenderingAction *> picking_actions;
        virtual void addAction(RenderingAction *action, bool common);
    public:
        LeveledRenderingManager();
        virtual void render();
        virtual void renderColored();
};
#endif	

