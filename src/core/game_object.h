#pragma once

#include "asset_manager.h"
#include "../common/types.h"

struct GameObject {
    public:
        static Model* model;
        static Transform transform;

        GameObject() = default;
        GameObject(const std::string& modelName);
        GameObject(const std::string& modelName, Shader& shader);
        void checkCollision();
        void update();
        
};