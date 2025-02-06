#pragma once

#include "material.hpp"
#include "vertex.hpp"
#include "drawCommand.hpp"
#include <vector>

struct Mesh {
    Material material;
    DrawElementsIndirectCommand drawCommand;

    Mesh() = default;
    Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
};