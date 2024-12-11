#include "input.h"
#include "../backend/backend.h"
#include <iostream>

namespace Input {
    GLFWwindow* _window = nullptr;
    bool _keyDown[372];
    bool _keyPressed[372];
    bool _keyDownLastFrame[372];
    glm::vec2 _mousePosOffset, _mousePos;
    int _scrollWheelYoffset;
    float _mouseSensitivity = 0.05f;

    const int NUM_MOUSE_BUTTONS = 8;
    bool _mouseButtonDown[NUM_MOUSE_BUTTONS];
    bool _mouseButtonPressed[NUM_MOUSE_BUTTONS];
    bool _mouseButtonDownLastFrame[NUM_MOUSE_BUTTONS];


    void init() {
        double x, y;
        _window = Backend::getWindowPointer();
        glfwSetScrollCallback(_window, _scroll_callback);
        glfwGetCursorPos(_window, &x, &y);
        _mousePos.x = (float)x;
        _mousePos.y = (float)y;
        _mousePosOffset = glm::vec2(0); // Initialize mouse offset

        // initialize mouse button connfigurations
        for (int button = 0; button < NUM_MOUSE_BUTTONS; button++) {
            _mouseButtonDown[button] = false;
            _mouseButtonPressed[button] = false;
            _mouseButtonDownLastFrame[button] = false;
        }
    }

    void update() {
        if (keyDown(SIN_KEY_ESCAPE)) {
            Backend::forceCloseWindow();
        }

        // Keyboard
        for (int key = 32; key < 349; key++) {
            _keyDown[key] = glfwGetKey(_window, key) == GLFW_PRESS;
            _keyPressed[key] = _keyDown[key] && !_keyDownLastFrame[key];
            _keyDownLastFrame[key] = _keyDown[key];
        }

        // Mouse
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        _mousePosOffset.x = (float)x - _mousePos.x;
        _mousePosOffset.y = (float)y - _mousePos.y;
        _mousePos.x = (float)x;
        _mousePos.y = (float)y;

        // Mouse buttons
        for (int button = 0; button < NUM_MOUSE_BUTTONS; button++) {
            _mouseButtonDown[button] = glfwGetMouseButton(_window, button) == GLFW_PRESS;
            _mouseButtonPressed[button] = _mouseButtonDown[button] && !_mouseButtonDownLastFrame[button];
            _mouseButtonDownLastFrame[button] = _mouseButtonDown[button];
        }
    }

    bool keyPressed(unsigned int key) {
        return _keyPressed[key];
    }

    bool keyDown(unsigned int key) {
        return _keyDown[key];
    }

    bool mouseButtonDown(int button) {
        return _mouseButtonDown[button];
    }

    bool mouseButtonPressed(int button) {
        return _mouseButtonPressed[button];
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