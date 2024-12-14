#pragma once

#include <glfw/glfw3.h>

namespace Clock {
    inline float time, _currentFrame, _lastFrame, dt;

    inline void update() {
        time = _currentFrame = glfwGetTime();
        dt = _currentFrame - _lastFrame;
        _lastFrame = _currentFrame;
        
    }
};