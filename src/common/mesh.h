#pragma once

#include "material.hpp"
#include "../api/opengl/types/shader.h"
#include <vector>

struct Mesh {
    Material material;
    DrawElementsIndirectCommand drawCommand;

    Mesh() = default;
    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
    void render(Shader* shader);
};