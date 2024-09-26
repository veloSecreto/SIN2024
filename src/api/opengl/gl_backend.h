#pragma once

#include "gl_renderer.h"
#include "../common/rendererCommon.h"

namespace OpenGLBackend {
    std::vector<uint32_t> globalVertices;
    std::vector<uint32_t> globalIndices;
    std::vector<DrawElementsIndirectCommand> drawCommands;

    void initMinimum();
    void uploadVertexData();
};