#pragma once

#include "../api/opengl/types/textureGenerator.h"
#include "../defines.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image/stb_image.h>


// todo: need more improvement

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex(const glm::vec3& position, const glm::vec3& normal, const glm::vec2& texCoord) {
        this->position = position;
        this->normal = normal;
        this->texCoord = texCoord;
    }

    Vertex(const glm::vec3& position, const glm::vec3& normal) {
        this->position = position;
        this->normal = normal;
    }

    Vertex(const glm::vec3& position) {
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
        uint32_t ID = -1;
        TextureType type;

        Texture() = default;

        Texture(const std::string& directory, TextureType type) {
            this->type = type;
            this->ID = generateTextureFromPath(directory);
        }
};

struct DrawElementsIndirectCommand {
    uint32_t indexCount;
    uint32_t instancedCount;
    uint32_t firstIndex;
    uint32_t baseVertex;
    uint32_t baseInstance;
};