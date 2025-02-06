#pragma once

#include "../../defines.h"
#include "types/shader.h"
#include "../../core/drawCommand.hpp"
#include "../../physics/aabb.hpp"
#include "types/shadow_map.h"

namespace OpenGLRenderer {
    extern uint32_t globalVAO;
    extern uint32_t globalVBO;
    extern uint32_t globalEBO;
    extern uint32_t globalIBO;
    extern uint32_t debugVAO;
    extern uint32_t debugVBO;
    extern std::unordered_map<std::string, Shader*> g_shaders;
    extern RenderMode renderMode;
    extern ShadowMap g_shadowMap;

    // shits
    extern bool _renderModeChanged;
    extern bool _debugging;

    void init();
    void uploadBuffersToGPU();
    void renderMesh(DrawElementsIndirectCommand& command);
    void renderFrame();
    void debugAABBs();
    void debugAABB(const AABB& aabb, const glm::vec3& color);
    void bindVAO();
    void unbindVAO();
    void beginFrame();
    void hotLoadShaders();
    void createShaders();
    void onResize();
    void onResize(float width, float height);
    Shader* getDefaultShader();
    Shader* getShaderByName(const std::string& name);
};