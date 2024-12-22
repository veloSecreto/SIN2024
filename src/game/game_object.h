#pragma once

#include "../core/asset_manager.h"
#include "../common/types.h"
#include "../common/aabb.hpp"
#include "_camera.h"
#include "../api/opengl/types/shader.h"

struct GameObject {
    public:
        Model model;
        Shader* shader;
        Transform transform;
        AABB aabb;
        Mesh _aabbMesh;

        GameObject() = default;
        GameObject(const std::string& modelName);
        void render();
        void update();
};