#pragma once

#include "../common.h"
#include "../api/gl_backend.h"
#include "../input/input.h"

namespace Backend {
    void init();
    void createWindow(const WindowMode& mode);

    GLFWwindow* getWindowPointer();
    API& getAPI();
    WindowMode& getWindowMode();
    bool windowIsOpen();
    void forceCloseWindow();

    void beginFrame();
    void endFrame();

    void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
};