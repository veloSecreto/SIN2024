#pragma once

#include <GLFW/glfw3.h>

namespace Clock {
    inline float time = 0.0f, _lastTime = 0.0f, _lastFrame = 0.0f, dt = 0.0f;
    inline int _frames = 0, fps = 0;

    inline void update() {
        // delta time mechanism
        time = (float)glfwGetTime();
        dt = time - _lastFrame;
        _lastFrame = time;
        // fps
        _frames++;
        if (time - _lastTime >= 1.0f) {
            fps = _frames;
            _frames = 0;
            _lastTime = time;
        }
    }
};