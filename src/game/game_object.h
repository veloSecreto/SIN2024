#pragma once

#include "../core/asset_manager.h"
#include "../common/types.h"
#include "_camera.h"
#include "../api/opengl/types/shader.h"

struct GameObject {
    public:
        static Model model;
        static Transform transform;
        static Shader shader;

        GameObject() = default;
        GameObject(const std::string& modelName, const std::string& shaderName);
        void checkCollision();
        void render();
        void update();
        
};