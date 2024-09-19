#include "input.h"

namespace Input {
    GLFWwindow* _window = nullptr;
    bool _keyDown[372];
    bool _keyPressed[372];
    bool _keyDownLastFrame[372];

    void init() {
        _window = Backend::getWindowPointer();
    }

    void update() {
        for (int key = 32; key < 349; key++) {
            if (glfwGetKey(_window, key) == GLFW_PRESS) {
                _keyDown[key] = true;
            }
            else {
                _keyDown[key] = false;
            }

            if (_keyDown[key] && !_keyDownLastFrame[key]) {
                _keyPressed[key] = true;
            }
            else {
                _keyPressed[key] = false;
            }
            _keyDownLastFrame[key] = _keyDown[key];
        }

        if (keyPressed(SIN_KEY_ESCAPE)) {
            Backend::forceCloseWindow();
        }
    }

    bool keyPressed(unsigned int key) {
        return _keyPressed[key];
    }

    bool keyDown(unsigned int key) {
        return _keyDown[key];
    }
}