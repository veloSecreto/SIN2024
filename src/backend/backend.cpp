#include "backend.h"
#include "../api/opengl/gl_backend.h"
#include "../input/input.h"
#include "../core/asset_manager.h"


namespace Backend {
    GLFWwindow* _window;
    GLFWmonitor* _monitor;
    API _api = API::OPENGL;

    WindowMode _windowMode = WindowMode::WINDOWED;

    int _width = 800;
    int _height = 600;

    bool _forceClose = false;


    void init() {
        glfwInit();
        glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n"; });
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        _monitor = glfwGetPrimaryMonitor();

        createWindow(_windowMode);
        glfwMakeContextCurrent(_window);

        if (_api == API::OPENGL) {
            OpenGLBackend::initMinimum();
            OpenGLRenderer::init();
            glfwSetFramebufferSizeCallback(_window, frameBufferSizeCallback);
        }
        else if (_api == API::VULKAN) {
            std::cout << "No initialization for Vulkan right now, fix this later" << std::endl;
        }
        else {
            std::cout << "No API defined, perhaps you forgot to define it." << std::endl;
            return;
        }
    }

    void createWindow(const WindowMode& mode) {
        if (mode == WindowMode::WINDOWED) {
            _window = glfwCreateWindow(_width, _height, "Unloved", nullptr, nullptr);
        }
        else {
            _window = glfwCreateWindow(_width, _height, "Unloved", _monitor, nullptr);
        }
        glfwHideWindow(_window);
    }

    void beginFrame() {
        glfwPollEvents();
        glfwGetWindowSize(_window, &_width, &_height);
    }

    void endFrame() {
        glfwSwapBuffers(_window);
    }

    void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    GLFWwindow* getWindowPointer() {
        return _window;
    }

    void forceCloseWindow() {
        _forceClose = true;
    }

    bool windowIsOpen() {
        return !glfwWindowShouldClose(_window) && !_forceClose;
    }

    API& getAPI() {
        return _api;
    }

    WindowMode& getWindowMode() {
        return _windowMode;
    }

    int& getWinWidth() {
        return _width;
    }

    int& getWinHeight() {
        return _height;
    }

    void show() {
        glfwShowWindow(_window);
    }

    void kill() {
        if (_window != nullptr) {
            glfwDestroyWindow(_window);
        }
        glfwTerminate();
    }
}