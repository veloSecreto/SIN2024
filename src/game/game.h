#pragma once

#include "../common.h"
#include "scene.h"

namespace Game {
    extern std::unordered_map<std::string, Scene> scenes;
    extern bool loaded;

    void init();
    void createScene(const std::string& name);
    void start();
    void render();
};