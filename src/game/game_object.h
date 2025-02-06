#pragma once

#include "../core/asset_manager.h"
#include "../physics/transform.hpp"
#include "../physics/aabb.hpp"
#include "_camera.h"

struct GameObject {
    public:
        std::string name;
        std::string _modelName;
        Model model;
        Transform transform;
        AABB aabb;

        GameObject() = default;
        GameObject(const std::string& modelName);
        void update();
};