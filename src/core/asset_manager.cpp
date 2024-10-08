#include "asset_manager.h"

// todo: need more improvement

std::unordered_map<std::string, Model*> AssetManager::g_models;
std::unordered_map<std::string, Texture> AssetManager::g_textures;

void AssetManager::loadAll() {
    findAllAssetPaths();
    loadForTesting();
}

void AssetManager::loadForTesting() {
    g_models.emplace("nurseGuy", new Model(ROOT_DIR + "res/models/nurseGuy.fbx"));
    // std::vector<Vertex> vertices = {
    //     Vertex(glm::vec3(-0.5f, -0.5f, 0.0f)),
    //     Vertex(glm::vec3( 0.5f, -0.5f, 0.0f)),
    //     Vertex(glm::vec3( 0.0f,  0.5f, 0.0f))
    // };

    // std::vector<uint32_t> indices = {0, 1, 2};
    // std::vector<Texture> textures = {};

    // Mesh(vertices, indices, textures);
}

void AssetManager::findAllAssetPaths() {
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/diffuse")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            std::string type = "diffuse";
            std::string path = ROOT_DIR + "res/textures/diffuse/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type, name));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/specular")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            std::string type = "specular";
            std::string path = ROOT_DIR + "res/textures/specular/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type, name));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }
}

Model* AssetManager::getModelByName(const std::string& name) {
    auto it = g_models.find(name);
    if (it != g_models.end()) {
        return it->second;
    } else {
        std::cerr << "Model '" << name << "' not found!" << std::endl;
        return nullptr;
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