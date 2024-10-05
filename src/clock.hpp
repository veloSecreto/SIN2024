#include "../common.h"

namespace Clock {
    auto _time = 0;
    float _currentFrame, _lastFrame, dt;

    void update() {
        _time = _currentFrame = glfwGetTime();
        dt = _currentFrame - _lastFrame;
        _lastFrame = _currentFrame;
        
    }
};