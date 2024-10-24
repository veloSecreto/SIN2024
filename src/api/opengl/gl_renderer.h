#pragma once

#include "../../common.h"
#include "types/shader.h"
<<<<<<< HEAD
#include "gl_backend.h"
#include "../../core/_camera.h"
#include <filesystem>

=======
#include "../../common/rendererCommon.h"
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

namespace OpenGLRenderer {
    extern uint32_t globalVAO;
    extern uint32_t globalVBO;
    extern uint32_t globalEBO;
    extern uint32_t globalIBO;
    extern std::unordered_map<std::string, Shader> g_shaders;

    void init();
    void uploadBuffersToGPU();
    void render(DrawElementsIndirectCommand& command);
<<<<<<< HEAD
=======
    void bindVAO();
    void unbindVAO();
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
    void beginFrame();
    void hotLoadShaders();
    void createShaders();
    Shader& getDefaultShader();
    Shader& getShaderByName(const std::string& name);
};