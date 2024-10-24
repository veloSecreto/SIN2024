#pragma once

#include "../common.h"
#include "game_object.h"
#include <vector>


class Scene {
    public:
        static std::vector<GameObject> gameObjects;
        
        Scene();
<<<<<<< HEAD
        void uploadToBackend();
=======
        void add(const GameObject& object);
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
        void update();
        void render();
};