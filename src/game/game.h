#pragma once

#include "../common.h"
#include "scene.h"

namespace Game {
    extern Scene scene;
    
    void init();
    void update();
    void render();
};