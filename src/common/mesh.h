#pragma once

#include "rendererCommon.h"
#include "../api/opengl/types/shader.h"

struct Mesh {
    std::vector<Texture> textures;
    DrawElementsIndirectCommand drawCommand;

    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, std::vector<Texture>& textures);
    void render(Shader* shader);
};