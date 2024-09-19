#include "gl_renderer.h"


namespace OpenGLRenderer {
    GLuint _vao, _vbo;
    struct Shaders {} g_shaders;
    
    void init() {
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);
    }

    void render() {
        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(_vao);
    }
};