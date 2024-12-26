#pragma once

#include "../common.h"
#include "game_object.h"
#include "lights.hpp"
#include "../api/opengl/types/skybox.hpp"
#include <vector>


class Scene {
    public:
        std::vector<GameObject> gameObjects;
        std::vector<Light> lights;
        Skybox skybox;
        
        Scene() = default;
        Scene(std::string skyboxPath, std::string skyboxFileFormat);
        void add(const GameObject& object);
        void add(const Light& light);
        void update();
        void render();
};