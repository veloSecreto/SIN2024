#pragma once

#include <glad/glad.h>
#include <iostream>

struct SSBO {
    GLuint ID;

    SSBO() : ID(0) {}

    void create(const void* data, GLsizeiptr size, GLuint index) {
        glCreateBuffers(1, &ID);
        if (ID == 0) {
            std::cerr << "Failed to create SSBO." << std::endl;
            return;
        }

        glNamedBufferData(ID, size, data, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ID);
    }

    void update(const void* data, GLsizeiptr size) {
        if (ID == 0) {
            std::cerr << "SSBO not created. Update failed." << std::endl;
            return;
        }

        static GLsizeiptr allocatedSize = 0;
        if (size > allocatedSize) {
            glNamedBufferData(ID, size, nullptr, GL_DYNAMIC_DRAW);
            allocatedSize = size;
        }

        glNamedBufferSubData(ID, 0, size, data);
    }

    GLsizeiptr getSize() const {
        GLint size;
        glGetNamedBufferParameteriv(ID, GL_BUFFER_SIZE, &size);
        return static_cast<GLsizeiptr>(size);
    }

    void cleanup() {
        if (ID) {
            glDeleteBuffers(1, &ID);
            ID = 0;
        }
    }

    ~SSBO() {
        cleanup();
    }
};
