#include "asset_manager.h"

// todo: need more improvement

std::unordered_map<std::string, Model*> AssetManager::g_models;
std::unordered_map<std::string, Texture> AssetManager::g_textures;

void AssetManager::loadAll() {
    findAllAssetPaths();
    loadForTesting();
}

void AssetManager::loadForTesting() {
    g_models.emplace("nurseGuy", new Model(ROOT_DIR + "res/models/nurseGuy/model.fbx"));
}

void AssetManager::findAllAssetPaths() {
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/diffuse")) {
        if (entry.is_regular_file()) {
            std::string key = entry.path().filename().string();
            std::string type = "diffuse";
            std::string path = ROOT_DIR + "res/textures/diffuse/" + key;
            g_textures.emplace(key, Texture(path, type, key));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/specular")) {
        if (entry.is_regular_file()) {
            std::string key = entry.path().filename().string();
            std::string type = "specular";
            std::string path = ROOT_DIR + "res/textures/specular/" + key;
            g_textures.emplace(key, Texture(path, type, key));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }
}

Model* AssetManager::getModelByName(const std::string& name) {
    return g_models.at(name);
}

Texture& AssetManager::getTextureByName(const std::string& name) {
    return g_textures.at(name);
}

/*Delta Corps Preist 1, Pagga, Electronic, ANSI Regular, ANSI Shadow*/ // for large comments