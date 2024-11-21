#pragma once

#include "gl_renderer.h"
#include "../../common/rendererCommon.h"
#include "types/ssbo.hpp"

namespace OpenGLBackend {
    extern std::vector<Vertex> globalVertices;
    extern std::vector<uint32_t> globalIndices;
    extern std::vector<DrawElementsIndirectCommand> drawCommands;
    extern std::unordered_map<std::string, SSBO> g_ssbos;

    void initMinimum();
    void createSSBOs();
    void uploadSSBOsToGPU();
    void updateSSBObyName(const std::string& name, const void* data, GLsizeiptr size);
    void uploadMeshData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, DrawElementsIndirectCommand& drawCommand);
};