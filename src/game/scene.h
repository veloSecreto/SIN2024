#pragma once

#include "../common.h"
#include "game_object.h"
#include <vector>


class Scene {
    public:
        static std::vector<GameObject> gameObjects;
        
        Scene();
        void uploadToBackend();
        void update();
        void render();
};