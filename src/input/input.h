#pragma once

#include "../common.h"
#include "../backend/backend.h"
#include "keycodes.h"

namespace Input {
    void init();
    void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    bool keyPressed(unsigned int key);
    bool keyDown(unsigned int key);
    glm::vec2 getMouseOffset();
    glm::vec2 getMousePos();
    void hideCursor();
    void unhideCursor();
    void disableCursor();
    float getMouseSensitivity();
    void setMouseSensitivity(float sensitivity);
    void update();
}