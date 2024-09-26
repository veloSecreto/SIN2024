#include "asset_manager.h"

// todo: need more improvement

namespace AssetManager {
    std::unordered_map<std::string, Model*> g_models;

    void loadAll();
    void loadForTesting();
    Model* getModelByName(const std::string& name);
};

void AssetManager::loadAll() {
    loadForTesting();
}

void AssetManager::loadForTesting() {
    g_models.emplace("backpack", new Model(ROOT_DIR + "res/models/backpack.obj"));
}

Model* AssetManager::getModelByName(const std::string& name) {
    return g_models.at(name);
} 

/*Delta Corps Preist 1, Pagga, Electronic, ANSI Regular, ANSI Shadow*/ // for large comments