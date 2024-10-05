#pragma once

#include "../../common.h"
#include "types/shader.h"
#include "gl_backend.h"
#include <filesystem>


namespace OpenGLRenderer {
    extern uint32_t globalVAO;
    extern uint32_t globalVBO;
    extern uint32_t globalEBO;
    extern uint32_t globalIBO;
    extern std::unordered_map<std::string, Shader> g_shaders;

    void init();
    void uploadBuffersToGPU();
    void render();
    void beginFrame();
    void hotLoadShaders();
    void createShaders();
    Shader& getDefaultShader();
    Shader& getShaderByName(const std::string& name);
};