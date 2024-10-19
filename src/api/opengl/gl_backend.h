#pragma once

#include "gl_renderer.h"
#include "../../common/rendererCommon.h"

namespace OpenGLBackend {
    extern std::vector<Vertex> globalVertices;
    extern std::vector<uint32_t> globalIndices;
    extern std::vector<DrawElementsIndirectCommand> drawCommands;

    void initMinimum();
    void uploadMeshData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, DrawElementsIndirectCommand& drawCommand);
};