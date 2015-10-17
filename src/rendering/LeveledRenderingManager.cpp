
#include "world/WorldManager.hpp"

#include "renderer/actions/RenderAllRooms.hpp"
#include "renderer/actions/RenderAllEntities.hpp"
#include "renderer/actions/RenderSkybox.hpp"
#include "renderer/actions/PositionLights.hpp"
#include "renderer/actions/RenderUI.hpp"
#include "ui/ui.hpp"
#include "rendering/LeveledRenderingManager.hpp"

LeveledRenderingManager::LeveledRenderingManager() {
    addAction(new PositionLights());
    addAction(new RenderAllRooms());
    addAction(new RenderAllEntities());
}

void LeveledRenderingManager::render() {
    this->renderer->beforeFrame();
    this->renderer->clear(ColorRGBA(0.5, 0.5, 0.5, 1));
    
    if(WorldManager::getInstance()->getCurrentWorld()) {
        this->renderer->enableTexturing(false);
        for(auto a: actions) {
            
            a->render();
        }
        //this->renderer->enableTexturing(true);
//        for(auto a: actions) {
//            
//            a->render();
//        }
    }
//     this->world = WorldManager::getInstance()->getCurrentWorld();
//    if (this->world) {
//        this->renderer->resetMatrix();
//        this->renderAllRooms();
//        cout << "w" << endl;
//    }
    this->renderer->resetMatrix();
    UI::getInstance()->getContext()->Render();
    UI::getInstance()->getContext()->Update();

    this->renderer->afterFrame();
    this->flush_callback();
}