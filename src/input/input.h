#pragma once

#include "../common.h"
#include "keycodes.h"

namespace Input {
    void init();
    void _scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    bool keyPressed(unsigned int key);
    bool keyDown(unsigned int key);
    const glm::vec2& getMouseOffset();
    const glm::vec2& getMousePos();
    const glm::vec3& getMouseRay();
    void hideCursor();
    void unhideCursor();
    void disableCursor();
    float getMouseSensitivity();
    void setMouseSensitivity(float sensitivity);
    float getMouseWheelYoffset();
    bool mouseButtonDown(int button);
    bool mouseButtonPressed(int button);
    static int getCursorState();
    void update();
}