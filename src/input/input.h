#pragma once

#include "../common.h"
#include "../backend/backend.h"
#include "keycodes.h"

namespace Input {
    void init();
    bool keyPressed(unsigned int key);
    bool keyDown(unsigned int key);
    void update();
}