
#include "world/WorldManager.hpp"

#include "renderer/actions/RenderAllRooms.hpp"
#include "renderer/actions/RenderAllEntities.hpp"
#include "renderer/actions/RenderSkybox.hpp"
#include "renderer/actions/PositionLights.hpp"
#include "renderer/actions/RenderUI.hpp"
#include "ui/ui.hpp"
#include "rendering/LeveledRenderingManager.hpp"

 void LeveledRenderingManager::addAction(RenderingAction *action, bool common) {
     RenderingManagerInterface::addAction(action);
     if(common) {
         picking_actions.push_back(action);
     }
 }

LeveledRenderingManager::LeveledRenderingManager() {
    addAction(new PositionLights(), false);
    addAction(new RenderSkybox(), false);
    addAction(new RenderAllRooms(), true);
    addAction(new RenderAllEntities(), true);
    addAction(new RenderUI(), false);
//    ui_action = new RenderUI();
//    ui_action->setRenderer(this->renderer);
}

void LeveledRenderingManager::render() {
    
    this->renderer->beforeFrame();
    this->renderer->clear(ColorRGBA(0.5, 0.5, 0.5, 1));
    this->renderer->enableTexturing(true);
    this->renderer->resetMatrix();
   
    if (WorldManager::getInstance()->getCurrentWorld()) {
        for (auto a : actions) {
            a->render();
        }
    } else {
        actions[actions.size()-1]->render();
    }
    
    
    this->renderer->afterFrame();
    this->flush_callback();
}

void LeveledRenderingManager::renderColored() {
    this->renderer->beforeFrame();
    this->renderer->clear(ColorRGBA(0.5, 0.5, 0.5, 1));
    this->renderer->resetMatrix();
    if (WorldManager::getInstance()->getCurrentWorld()) {
        this->renderer->enableTexturing(false);
        for (auto a : picking_actions) {
            a->render();
        }
    }
    this->renderer->afterFrame();
    this->flush_callback();
}