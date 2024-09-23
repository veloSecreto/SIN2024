#include "backend.h"


namespace Backend {
    GLFWwindow* _window;
    GLFWmonitor* _monitor;
    API _api = API::OPENGL;

    WindowMode _windowMode = WindowMode::WINDOWED;

    int _width = 1200;
    int _height = 665;

    bool _forceClose = false;

    // Initialzes the Back-End system itself and the renderer specified by the API
    // ---------------------------------------------------------------------------
    void init() {
        glfwInit();
        glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n"; });


        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _monitor = glfwGetPrimaryMonitor();

        createWindow(_windowMode);

        glfwMakeContextCurrent(_window);


        if (_api == API::OPENGL) {
            OpenGLBackend::initMinimum();
            std::cout << "OpenGL Version ==> " << glGetString(GL_VERSION) << std::endl;
            OpenGLRenderer::init();
            glViewport(0, 0, _width, _height);
            glfwSetFramebufferSizeCallback(_window, frameBufferSizeCallback);
        }
        else if (_api == API::VULKAN) {
            // todo: Implement Vulkan initialization
            std::cout << "No initialization for Vulkan right now, fix this later" << std::endl;
        }
        else {
            std::cout << "No API defined, perhaps you forgot to define it." << std::endl;
            return;
        }
    }

    // Creates GLFW window according to the given WindowMode ENUM
    // ----------------------------------------------------------
    void createWindow(const WindowMode& mode) {
        if (mode == WindowMode::WINDOWED) {
            _window = glfwCreateWindow(_width, _height, "Unloved", nullptr, nullptr);
        }
        else {
            _window = glfwCreateWindow(_width, _height, "Unloved", _monitor, nullptr);
        }
    }

    // Begins BackEnd render frame
    // ---------------------------
    void beginFrame() {
        glfwPollEvents();
    }

    // Ends BackEnd render frame
    // -------------------------
    void endFrame() {
        glfwSwapBuffers(_window);
    }

    // calls the frame buffer size whenever the window is resized
    // ----------------------------------------------------------
    void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    // Returns the window (Pointer)
    // ----------------------------
    GLFWwindow* getWindowPointer() {
        return _window;
    }

    // Closes the window forcibly
    // --------------------------
    void forceCloseWindow() {
        _forceClose = true;
    }

    // Return true if the window is open else it returns false
    // -------------------------------------------------------
    bool windowIsOpen() {
        return !glfwWindowShouldClose(_window) && !_forceClose;
    }

    // Returns the current API (Check src/common.h for possible APIs)
    // --------------------------------------------------------------
    API& getAPI() {
        return _api;
    }

    // Returns the current Window Mode (Check src/common.h for possible Window Modes)
    // ------------------------------------------------------------------------------
    WindowMode& getWindowMode() {
        return _windowMode;
    }
}