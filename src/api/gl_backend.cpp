#include "gl_backend.h"

namespace OpenGLBackend {
    void initMinimum() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            std::cout << "Couldn't Initialize GLAD" << std::endl;
        }
    }
}