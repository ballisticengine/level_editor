#include "RenderingManager.hpp"

#include "ui/ui.hpp"

void LeveledRenderingManager::render() {
    this->renderer->beforeFrame();
    this->renderer->resetMatrix();
    UI::getInstance()->getContext()->Render();
    UI::getInstance()->getContext()->Update();
    this->renderer->afterFrame();
    this->flush_callback();
}