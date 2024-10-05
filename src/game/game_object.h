#pragma once

#include "../core/asset_manager.h"
#include "../common/types.h"

struct GameObject {
    public:
        static Model* model;
        static Transform transform;
        static Shader shader;

        GameObject() = default;
        GameObject(const std::string& modelName);
        GameObject(const std::string& modelName, const std::string& shaderName);
        void checkCollision();
        void update();
        
};