#pragma once

#include "common.h"

namespace Clock {
    inline float _time, _currentFrame, _lastFrame, dt;

    inline void update() {
        _time = _currentFrame = glfwGetTime();
        dt = _currentFrame - _lastFrame;
        _lastFrame = _currentFrame;
        
    }
};