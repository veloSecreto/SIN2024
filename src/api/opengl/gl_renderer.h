#pragma once

#include "../../common.h"
#include "types/shader.h"
#include "../../common/rendererCommon.h"

namespace OpenGLRenderer {
    extern uint32_t globalVAO;
    extern uint32_t globalVBO;
    extern uint32_t globalEBO;
    extern uint32_t globalIBO;
    extern std::unordered_map<std::string, Shader*> g_shaders;

    void init();
    void uploadBuffersToGPU();
    void render(DrawElementsIndirectCommand& command);
    void bindVAO();
    void unbindVAO();
    void beginFrame();
    void hotLoadShaders();
    void createShaders();
    Shader* getDefaultShader();
    Shader* getShaderByName(const std::string& name);
    void render();
};