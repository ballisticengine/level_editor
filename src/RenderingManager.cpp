#include "RenderingManager.hpp"

#include "ui/ui.hpp"

void LeveledRenderingManager::render() {
    this->renderer->beforeFrame();
    this->renderer->clear(ColorRGBA(0.5,0.5,0.5,1));
    this->renderer->resetMatrix();
    UI::getInstance()->getContext()->Render();
    UI::getInstance()->getContext()->Update();
    this->renderer->afterFrame();
    this->flush_callback();
}