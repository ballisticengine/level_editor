#include "RenderingManager.hpp"
#include "world/WorldManager.hpp"

#include "ui/ui.hpp"

void LeveledRenderingManager::render() {
    this->renderer->beforeFrame();
    this->renderer->clear(ColorRGBA(0.5, 0.5, 0.5, 1));
     this->world = WorldManager::getInstance()->getCurrentWorld();
    if (this->world) {
        this->renderer->resetMatrix();
        this->renderAllRooms();
        cout << "w" << endl;
    }
    this->renderer->resetMatrix();
    UI::getInstance()->getContext()->Render();
    UI::getInstance()->getContext()->Update();

    this->renderer->afterFrame();
    this->flush_callback();
}