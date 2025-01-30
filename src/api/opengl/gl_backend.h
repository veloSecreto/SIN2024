#pragma once

#include "../../core/vertex.hpp"
#include "../../core/drawCommand.hpp"
#include "types/ssbo.hpp"
#include "types/instance_data.h"
#include "types/g_buffer.hpp"
#include "types/texture_array.h"
#include <vector>

namespace OpenGLBackend {
    extern std::vector<Vertex> globalVertices;
    extern std::vector<uint32_t> globalIndices;
    extern std::vector<DrawElementsIndirectCommand> drawCommands;
    extern std::vector<Vertex> debugVertices;
    extern std::unordered_map<std::string, SSBO> g_ssbos;
    extern std::vector<InstanceData> instances;
    extern GBuffer gbuffer;
    extern TextureArray g_textureArray;

    void initMinimum();
    void createSSBOs();
    void uploadSSBOsToGPU();
    void update();
    void configureFramebuffers();
    void uploadMeshData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    void upload();
};