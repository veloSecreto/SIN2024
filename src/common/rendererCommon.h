#pragma once

#include "../common.h"
#include "../api/opengl/types/textureGenerator.h"
#include <stb_image/stb_image.h>


// todo: need more improvement

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord) {
        this->position = position;
        this->normal = normal;
        this->texCoord = texCoord;
    }

    Vertex(glm::vec3 position, glm::vec3 normal) {
        this->position = position;
        this->normal = normal;
    }

    Vertex(glm::vec3 position) {
        this->position = position;
    }

    Vertex() {
        this->position = glm::vec3(0.0f);
        this->normal = glm::vec3(0.0f);
        this->texCoord = glm::vec2(0.0f);
    }
};

struct Texture {
    public:
        unsigned int index;
        TextureType type;

        Texture(const std::string& directory, TextureType type, unsigned int index) {
            this->type = type;
            this->index = index;
            generateTextureFromPath(directory);
        }
};

struct DrawElementsIndirectCommand {
    uint32_t indexCount;
    uint32_t instancedCount;
    uint32_t firstIndex;
    uint32_t baseVertex;
    uint32_t baseInstance;
};