#include "g_buffer.hpp"
#include "../gl_renderer.h"
#include "../../../clock.hpp"

void GBuffer::configure(const unsigned int& width, const unsigned int& height) {
        if (ID == 0) {
            glGenFramebuffers(1, &ID);
            glGenTextures(1, &albedo);
            glGenTextures(1, &depth);
            this->width = width;
            this->height = height;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, ID);

        glBindTexture(GL_TEXTURE_2D, albedo);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, albedo, 0);

        glBindTexture(GL_TEXTURE_2D, depth);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth, 0);
    
        auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (fboStatus != GL_FRAMEBUFFER_COMPLETE) std::cout << "G-Framebuffer configuration error from GL\n" << fboStatus << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);


    float __gBufferVertices[] = {
    //  pos              texCoord
        1, -1,           1, 0,
       -1, -1,           0, 0,
       -1,  1,           0, 1,
        1,  1,           1, 1,
        1, -1,           1, 0,
       -1,  1,           0, 1
    };

    uint32_t _vbo;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(__gBufferVertices), &__gBufferVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

    shader = OpenGLRenderer::getShaderByName("g-buffer");
    shader->use();
    shader->setInt("albedo", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo);
}

void GBuffer::draw() {
    glBindVertexArray(VAO);
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedo);
    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void GBuffer::destroy() {
    glDeleteTextures(1, &albedo);
    glDeleteRenderbuffers(1, &depth);
    glDeleteFramebuffers(1, &ID);
}

GBuffer::~GBuffer() {
    destroy();
}

void GBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, ID);
}
