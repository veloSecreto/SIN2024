#pragma once

#include <glm/glm.hpp>

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
        this->texCoord = glm::vec3(0);
    }

    Vertex(const glm::vec3& position) {
        this->position = position;
        this->normal = glm::vec3(0.0f);
        this->texCoord = glm::vec2(0.0f);
    }

    Vertex() {
        this->position = glm::vec3(0.0f);
        this->normal = glm::vec3(0.0f);
        this->texCoord = glm::vec2(0.0f);
    }
};