#pragma once

#include "material.hpp"
#include "../api/opengl/types/shader.h"

struct Mesh {
    Material material;
    DrawElementsIndirectCommand drawCommand;

    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    void render(Shader* shader);
};