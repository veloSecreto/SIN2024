#pragma once

#include "../core/asset_manager.h"
#include "../common/types.h"
<<<<<<< HEAD
#include "../core/_camera.h"
=======
#include "_camera.h"
#include "../api/opengl/types/shader.h"
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

struct GameObject {
    public:
        static Model* model;
        static Transform transform;
<<<<<<< HEAD

        GameObject() = default;
        GameObject(const std::string& modelName);
        void checkCollision();
=======
        static Shader shader;

        GameObject() = default;
        GameObject(const std::string& modelName, const std::string& shaderName);
        void checkCollision();
        void render();
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
        void update();
        
};