#pragma once

#include "../common.h"
<<<<<<< HEAD

namespace Game {
      
=======
#include "scene.h"

namespace Game {
    extern std::unordered_map<std::string, Scene> scenes;
    extern bool loaded;

    void init();
    void createScene(const std::string& name);
    void start();
    void render();
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
};