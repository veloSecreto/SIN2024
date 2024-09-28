#pragma once

#include "../common.h"
#include "../api/opengl/gl_backend.h"
#include "../input/input.h"
#include "../core/asset_manager.h"

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