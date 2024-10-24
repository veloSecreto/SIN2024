#pragma once

#include "../common.h"
#include "game_object.h"
#include <vector>


class Scene {
    public:
        static std::vector<GameObject> gameObjects;
        
        Scene();
        void add(const GameObject& object);
        void update();
        void render();
};