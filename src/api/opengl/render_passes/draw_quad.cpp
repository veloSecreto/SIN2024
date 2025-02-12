#include "render_passes.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static GLuint quadVAO = 0;
bool initialized = false;

void DrawQuad() {
    if (!initialized) {
        float __quadVertices[] = {
            //  pos              texCoord
             1, -1,           1, 0,
            -1, -1,           0, 0,
            -1,  1,           0, 1,
             1,  1,           1, 1,
             1, -1,           1, 0,
            -1,  1,           0, 1
        };
    
        uint32_t _vbo;
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);
        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(__quadVertices), &__quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glBindVertexArray(0);

        initialized = true;
    }
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}