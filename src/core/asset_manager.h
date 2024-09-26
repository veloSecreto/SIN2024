#pragma once

#include "../common.h"
#include "../common/model.h"
#include <vector>

namespace AssetManager {
    void loadAll();
    void loadForTesting();
    void loadModel();
    void loadTexture();
    Model* getModelByName(const std::string& name);
};