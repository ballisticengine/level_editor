#include "LevelChange.hpp"

#include "config/EngineState.hpp"
#include "world/WorldManager.hpp"
#include "resources/ResourceManager.hpp"
#include "libload/LibLoad.hpp"
#include "rendering/LeveledRenderingManager.hpp"

void LevelChange::before(StateChangeData data) {

}

void LevelChange::after(StateChangeData data) {
    Loader *l = (Loader *) LibLoad::getInstance()->getLoaderByExtension("xml", LEVEL);
    string lvl = *(string *) data.value;
    if(lvl=="") {
        cout << "Empty level" << endl;
        return;
    }
    cout << "level changed to: " << lvl << endl;
    ResourceManager::getInstance()->setWD(EngineState::getInstance()->getString("engine_wd") + "/data");
    ResourceManager::getInstance()->setLevel(lvl);
    World *w = (World*) ResourceManager::getInstance()->get("level.xml", LEVEL);
    ResourceManager::getInstance()->resolveAllDependencies();
    WorldManager::getInstance()->setWorld(w);
    WorldManager::getInstance()->getCurrentWorld()->colorize();
    for (auto a : LeveledRenderingManager::getInstance()->getActions()) {
        a->setWorld(w);
    }

    vector<LoadedResource *> ts = ResourceManager::getInstance()->getByType(TEXTURE);

    size_t ts_size = ts.size();
    for (size_t i = 0; i < ts_size; i++) {

        if (ts[i]->object) {
            LeveledRenderingManager::getInstance()
                    ->getRenderer()
                    ->setupTexture((Ballistic::Types::Texture *) ts[i]->object);
        }
    }

}
