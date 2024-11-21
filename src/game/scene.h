#pragma once

#include "../common.h"
#include "game_object.h"
#include "lights.hpp"
#include <vector>


class Scene {
    public:
        std::vector<GameObject> gameObjects;
        std::vector<Light> lights;
        
        Scene();
        void add(const GameObject& object);
        void addLight(const Light& light);
        void update();
        void render();
};