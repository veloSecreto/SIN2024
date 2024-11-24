#include "input.h"
#include "../backend/backend.h"

namespace Input {
    GLFWwindow* _window = nullptr;
    bool _keyDown[372];
    bool _keyPressed[372];
    bool _keyDownLastFrame[372];
    glm::vec2 _mousePosOffset, _mousePos;
    int _scrollWheelYoffset;
    float _mouseSensitivity = 0.05f;

    void init() {
        double x, y;
        _window = Backend::getWindowPointer();
        glfwSetScrollCallback(_window, _scroll_callback);
        glfwGetCursorPos(_window, &x, &y);
        _mousePos.x = (float)x;
        _mousePos.y = (float)y;
        _mousePosOffset = glm::vec2(0); // Initialize mouse offset
    }

    void update() {
        // Keyboard
        for (int key = 32; key < 349; key++) {
            if (glfwGetKey(_window, key) == GLFW_PRESS) {
                _keyDown[key] = true;
            } else {
                _keyDown[key] = false;
            }

            if (_keyDown[key] && !_keyDownLastFrame[key]) {
                _keyPressed[key] = true;
            } else {
                _keyPressed[key] = false;
            }
            _keyDownLastFrame[key] = _keyDown[key];
        }

        // Mouse
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        _mousePosOffset.x = (float)x - _mousePos.x;
        _mousePosOffset.y = (float)y - _mousePos.y;
        _mousePos.x = (float)x;
        _mousePos.y = (float)y;

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

    glm::vec2 getMouseOffset() {
        return _mousePosOffset;
    }
    
    glm::vec2 getMousePos() {
        return _mousePos;
    }

    void _scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset) {
        _scrollWheelYoffset = (int)yoffset;
    }

    void hideCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    }

    void unhideCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    void disableCursor() {
        glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    float getMouseSensitivity() {
        return _mouseSensitivity;
    }

    void setMouseSensitivity(float sensitivity) {
        _mouseSensitivity = sensitivity;
    }

    float getMouseWheelYoffset() {
        return 0;
    }
}