#pragma once

#include "../common.h"
#include "scene.h"

namespace Game {
    extern Scene scene;
    
    void start();
    void update();
    void render();
};