#pragma once

#include <cstdint>

struct DrawElementsIndirectCommand {
    uint32_t indexCount;
    uint32_t instancedCount;
    uint32_t firstIndex;
    uint32_t baseVertex;
    uint32_t baseInstance;
};