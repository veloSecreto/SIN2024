#pragma once

#include "../common.h"
#include "model.h"
#include "texture.hpp"
#include <vector>
#include <filesystem>

namespace AssetManager {
    extern std::unordered_map<std::string, Model> g_models;
    extern std::unordered_map<std::string, Texture> g_textures;

    void loadAll();
    void findAllAssetPaths();
    void loadModels();
    Model& getModelByName(const std::string& name);
    Texture& getTextureByName(const std::string& name);
};