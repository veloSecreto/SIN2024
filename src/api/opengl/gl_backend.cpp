#include "gl_backend.h"

namespace OpenGLBackend {

    // Initializes the OpenGL Backend system for rendering
    // ---------------------------------------------------
    void initMinimum() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Couldn't Initialize GLAD" << std::endl;
        }
    }
}