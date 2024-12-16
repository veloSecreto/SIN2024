#pragma once

#include "../common.h"
#include "../common/model.h"
#include "../common/rendererCommon.h"
#include <vector>
#include <filesystem>

namespace AssetManager {
    extern std::unordered_map<std::string, Model> g_models;
    extern std::unordered_map<std::string, Texture> g_textures;

    void loadAll();
    void findAllAssetPaths();
    void loadModels();
    void loadModel();
    void loadTexture();
    Model& getModelByName(const std::string& name);
    Texture& getTextureByName(const std::string& name);
};