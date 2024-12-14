#pragma once

#include "gl_renderer.h"
#include "../../common/rendererCommon.h"
#include "types/ssbo.hpp"
#include "types/g_buffer.hpp"

namespace OpenGLBackend {
    extern std::vector<Vertex> globalVertices;
    extern std::vector<uint32_t> globalIndices;
    extern std::vector<DrawElementsIndirectCommand> drawCommands;
    extern std::unordered_map<std::string, SSBO> g_ssbos;
    extern GBuffer gbuffer;
    extern std::vector<uint64_t> textureHandles;

    void initMinimum();
    void createSSBOs();
    void uploadSSBOsToGPU();
    void updateSSBObyName(const std::string& name, const void* data, GLsizeiptr size);
    void update();
    void configureFBOs();
    void uploadMeshData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, DrawElementsIndirectCommand& drawCommand);
};