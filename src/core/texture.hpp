#pragma once

#include "../api/opengl/types/textureGenerator.h"
#include "../defines.h"

struct Texture {
public:
    uint32_t handle = -1;
    TextureType type;

    Texture() = default;

    Texture(const std::string& directory, TextureType type) {
        this->type = type;
        this->handle = generateTextureFromPath(directory);
    }
};