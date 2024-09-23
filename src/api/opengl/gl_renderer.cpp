#include "gl_renderer.h"


namespace OpenGLRenderer {
    
    // Initializes the OpenGL Renderer
    // -------------------------------
    void init() {
        std::cout << "OpenGL Renderer initialized" << std::endl;
    }

    // Renders everything (OpenGL API)
    // -------------------------------
    void render() {
        // render here
    }

    void beginFrame() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    }
};