#pragma once

#include "../../common.h"
#include "types/shader.h"
#include "gl_backend.h"


namespace OpenGLRenderer {
    void init();
    void uploadBuffersToGPU();
    void render();
    void beginFrame();
    Shader& getDefaultShader();
};