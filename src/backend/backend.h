#pragma once

#include "../common.h"

namespace Backend {
    void init();
    void createWindow(const WindowMode& mode);
    void show();

    GLFWwindow* getWindowPointer();
    API& getAPI();
    WindowMode& getWindowMode();
    bool windowIsOpen();
    void forceCloseWindow();
    void kill();

    void beginFrame();
    void endFrame();
    
    int& getWinWidth();
    int& getWinHeight();

    void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
};