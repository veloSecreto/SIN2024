#pragma once

#include "../core/asset_manager.h"
#include "../common/types.h"
#include "../core/_camera.h"

struct GameObject {
    public:
        static Model* model;
        static Transform transform;

        GameObject() = default;
        GameObject(const std::string& modelName);
        void checkCollision();
        void update();
        
};