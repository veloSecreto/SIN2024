#pragma once

#include "../common.h"
#include "scene.h"

namespace Game {
    extern std::unordered_map<std::string, Scene> scenes;
    extern bool loaded;
    extern GameObject object, object2;
    
    void createScene(const std::string& name);
    void start();
    void render();
};