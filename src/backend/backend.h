#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../common.h"
#include "../api/gl_backend.h"
#include "../input/input.h"

using namespace std;

namespace Backend {
    void init();
    void createWindow(const WindowMode& mode);

    GLFWwindow* getWindowPointer();
    bool windowIsOpen();
    void forceCloseWindow();

    void beginFrame();
    void endFrame();
};