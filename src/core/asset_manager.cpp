#include "asset_manager.h"

// todo: need more improvement

std::unordered_map<std::string, Model> AssetManager::g_models;
std::unordered_map<std::string, Texture> AssetManager::g_textures;

void AssetManager::loadAll() {
    findAllAssetPaths();
    loadModels();
}



/*
 █▄█ █▀█ █▀▄ █▀▀ █   █▀▀
 █ █ █ █ █ █ █▀▀ █   ▀▀█
 ▀ ▀ ▀▀▀ ▀▀  ▀▀▀ ▀▀▀ ▀▀▀
*/

void AssetManager::loadModels() {
    g_models["mushroom"] =  Model(ROOT_DIR + "res/models/mushroom.obj");
    // mushroom material setup
    {
        Material newMat;
        newMat.setParameter(TextureType::ALBEDO, "tree_mushroom_BaseColor");
        newMat.setParameter(TextureType::ROUGHNESS, "tree_mushroom_Roughness");
        newMat.setParameter(TextureType::METALLIC, "Ch16_1002_Specular");
        newMat.setParameter(TextureType::AO, "tree_mushroom_AO");

        g_models["mushroom"].setMaterial(0, newMat);
    }

    g_models["nurseGuy"] = Model(ROOT_DIR + "res/models/nurseGuy.obj");
    // nurseGuy's materials
    {
        Material nurseMat;
        nurseMat.setParameter(TextureType::ALBEDO, "Ch16_1001_Diffuse");
        nurseMat.setParameter(TextureType::ROUGHNESS, glm::vec3(0.7));
        nurseMat.setParameter(TextureType::METALLIC, "Ch16_1001_Specular");
        nurseMat.setParameter(TextureType::AO, glm::vec3(1));
        Material nurseMat2;
        nurseMat2.setParameter(TextureType::ALBEDO, "Ch16_1002_Diffuse");
        nurseMat2.setParameter(TextureType::ROUGHNESS, glm::vec3(0.7));
        nurseMat2.setParameter(TextureType::METALLIC, "Ch16_1002_Specular");
        nurseMat2.setParameter(TextureType::AO, glm::vec3(1));

        g_models["nurseGuy"].setMaterial(0, nurseMat);   // head, hand, shoes
        g_models["nurseGuy"].setMaterial(1, nurseMat);   // shirt
        g_models["nurseGuy"].setMaterial(2, nurseMat);   // pants
        g_models["nurseGuy"].setMaterial(3, nurseMat2);  // mask
        g_models["nurseGuy"].setMaterial(4, nurseMat2);  // eyebrows
        g_models["nurseGuy"].setMaterial(5, nurseMat2);  // hat
        g_models["nurseGuy"].setMaterial(6, nurseMat2);  // shoes (idk why twice)
    }

    g_models["sphere"] = Model(ROOT_DIR + "res/models/sphere.obj");
    // sphere materials
    {
        Material mat;
        mat.setParameter(TextureType::ALBEDO, glm::vec3(0.5f, 0, 0));
        mat.setParameter(TextureType::ROUGHNESS, glm::vec3(0.7f));
        mat.setParameter(TextureType::METALLIC, glm::vec3(0.5f));
        mat.setParameter(TextureType::AO, glm::vec3(1));

        g_models["sphere"].setMaterial(0, mat);
    }

    g_models["cube"] = Model(ROOT_DIR + "res/models/cube.obj");
    // cube materialls
    {
        Material cubeMat;
        cubeMat.setParameter(TextureType::ALBEDO, "Floorboards_ALB");
        cubeMat.setParameter(TextureType::ROUGHNESS, "Floorboards_R");
        cubeMat.setParameter(TextureType::METALLIC, "metalic_blank");
        cubeMat.setParameter(TextureType::AO, "Floorboards_AO");

        g_models["cube"].setMaterial(0, cubeMat);
    }

    g_models["house"] = Model(ROOT_DIR + "res/models/house.obj");
    // house material stuffs
    {
        Material houseMat;
        houseMat.setParameter(TextureType::ALBEDO, "Ceiling_ALB");
        houseMat.setParameter(TextureType::ROUGHNESS, "Ceiling_R");
        houseMat.setParameter(TextureType::METALLIC, "metalic_blank");
        houseMat.setParameter(TextureType::AO, "Ceiling_AO");

        g_models["house"].setMaterial(0, houseMat);
        g_models["house"].setMaterial(1, houseMat);
        g_models["house"].setMaterial(2, houseMat);
        g_models["house"].setMaterial(3, houseMat);
        g_models["house"].setMaterial(4, houseMat);
        g_models["house"].setMaterial(5, houseMat);
        g_models["house"].setMaterial(6, houseMat);
        g_models["house"].setMaterial(7, houseMat);
        g_models["house"].setMaterial(8, houseMat);
        g_models["house"].setMaterial(9, houseMat);
        g_models["house"].setMaterial(10, houseMat);
        g_models["house"].setMaterial(11, houseMat);
        g_models["house"].setMaterial(12, houseMat);
        g_models["house"].setMaterial(13, houseMat);
        g_models["house"].setMaterial(14, houseMat);
        g_models["house"].setMaterial(15, houseMat);
    }

    std::cout << "nurseGuy has " << g_models["nurseGuy"].meshes.size() << " meshes" << std::endl;
    g_models["room"] = Model(ROOT_DIR + "res/models/room.obj");
    // room materiial setttings
    {
        Material roomMat;
        roomMat.setParameter(TextureType::ALBEDO, "Ceiling_ALB");
        roomMat.setParameter(TextureType::ROUGHNESS, "Ceiling_R");
        roomMat.setParameter(TextureType::METALLIC, "metalic_blank");
        roomMat.setParameter(TextureType::AO, "Ceiling_AO");

        g_models["room"].setMaterial(0, roomMat);
        g_models["room"].setMaterial(1, roomMat);
        g_models["room"].setMaterial(2, roomMat);
        g_models["room"].setMaterial(3, roomMat);
    }
}

/*
 █   █▀█ █▀█ █▀▄   █▀▀ █▀▄ █▀█ █▄█   █▀▄ ▀█▀ █▀▀ █ █
 █   █ █ █▀█ █ █   █▀▀ █▀▄ █ █ █ █   █ █  █  ▀▀█ █▀▄
 ▀▀▀ ▀▀▀ ▀ ▀ ▀▀    ▀   ▀ ▀ ▀▀▀ ▀ ▀   ▀▀  ▀▀▀ ▀▀▀ ▀ ▀
*/

void AssetManager::findAllAssetPaths() {
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/diffuse")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::ALBEDO;
            std::string path = ROOT_DIR + "res/textures/diffuse/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/roughness")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::ROUGHNESS;
            std::string path = ROOT_DIR + "res/textures/roughness/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }
    
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/metallic")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::METALLIC;
            std::string path = ROOT_DIR + "res/textures/metallic/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type));
            std::cout << "Loaded texture from path: " << path << std::endl;
        }
    }

    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/textures/ao")) {
        if (entry.is_regular_file()) {
            std::string name = entry.path().filename().string();
            TextureType type = TextureType::AO;
            std::string path = ROOT_DIR + "res/textures/ao/" + name;
            name = name.substr(0, name.find_last_of('.'));
            g_textures.emplace(name, Texture(path, type));
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