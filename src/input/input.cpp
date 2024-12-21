#include "input.h"
#include "../backend/backend.h"
#include "../game/_camera.h"
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

    // optimization configuration
    bool mouseStateChanged = false;
    int prevMouseState, currentMouseState;

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

        // optimizations
        currentMouseState = getCursorState();
        mouseStateChanged = currentMouseState != prevMouseState;
        prevMouseState = currentMouseState;
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
        if (!mouseStateChanged) {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
    }

    void unhideCursor() {
        if (!mouseStateChanged) {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }

    void disableCursor() {
        if (!mouseStateChanged) {
            glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
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

    static int getCursorState() {
        return glfwGetInputMode(_window, GLFW_CURSOR);
    }

    glm::vec3 getMouseRay() {
        float x = (2.0f * _mousePos.x) / (float)Backend::getWinWidth() - 1.0f;
        float y = 1.0f - (2.0f * _mousePos.y) / (float)Backend::getWinHeight();
        float z = 1.0f;
        glm::vec3 ray_nds = glm::vec3(x, y, z);
        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, ray_nds.z, 1.0f);
        glm::vec4 ray_eye = glm::inverse(Camera::m_proj) * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, ray_eye.z, 0.0f);
        glm::vec4 inv_ray_wor = (inverse(Camera::m_view) * ray_eye);
        glm::vec3 ray_wor = glm::vec3(inv_ray_wor.x, inv_ray_wor.y, inv_ray_wor.z);
        ray_wor = normalize(ray_wor);
        return ray_wor;
    }
}