#include "backend.h"


namespace Backend {
    GLFWwindow* _window;
    GLFWmonitor* _monitor;
    API _api = API::OPENGL;

    WindowMode _windowedMode = WindowMode::WINDOWED;

    int _width = 1200;
    int _height = 665;

    bool _forceClose = false;

    void init() {
        glfwInit();
        glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n";});


        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _monitor = glfwGetPrimaryMonitor();

        createWindow(_windowedMode);

        glfwMakeContextCurrent(_window);
        
        if (_api == API::OPENGL) {
            OpenGLBackend::initMinimum();
        }
        else if (_api == API::VULKAN) {
            cout << "No initialization for Vulkan right now, fix this later" << endl;
        }
        else {
            cout << "No API defined, perhaps you forgot to define it." << endl;
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
    }

    void beginFrame() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glfwPollEvents();
    }

    void endFrame() {
        glfwSwapBuffers(_window);
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
}