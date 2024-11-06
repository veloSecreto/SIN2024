#include "asset_manager.h"

// todo: need more improvement

std::unordered_map<std::string, Model> AssetManager::g_models;
std::unordered_map<std::string, Texture> AssetManager::g_textures;

void AssetManager::loadAll() {
    findAllAssetPaths();
    loadForTesting();
}

void AssetManager::loadForTesting() {
    g_models["mushroom"] =  Model(ROOT_DIR + "res/models/mushroom.obj");
    g_models["nurseGuy"] =  Model(ROOT_DIR + "res/models/nurseGuy.obj");
    g_models["point_light_core"] = Model(ROOT_DIR + "res/models/point_light_core.obj");
    g_models["point_light_blend"] = Model(ROOT_DIR + "res/models/point_light_blend.obj");
}

void AssetManager::findAllAssetPaths() {
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/diffuse")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::DIFFUSE;
            std::string path = ROOT_DIR + "res/textures/diffuse/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type, name));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/specular")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::SPECULAR;
            std::string path = ROOT_DIR + "res/textures/specular/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type, name));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/emissive")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::EMISSIVE;
            std::string path = ROOT_DIR + "res/textures/emissive/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type, name));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }
}

Model& AssetManager::getModelByName(const std::string& name) {
    auto it = g_models.find(name);
    if (it != g_models.end()) {
        return it->second;
    } else {
        std::cerr << "Model '" << name << "' not found!" << std::endl;
        throw std::runtime_error("Model not found");
    }
}

Texture& AssetManager::getTextureByName(const std::string& name) {
    auto it = g_textures.find(name);
    if (it != g_textures.end()) {
        return it->second;
    } else {
        std::cerr << "Texture '" << name << "' not found!" << std::endl;
        throw std::runtime_error("Texture not found");
    }
}

/*Delta Corps Preist 1, Pagga, Electronic, ANSI Regular, ANSI Shadow*/ // for large comments