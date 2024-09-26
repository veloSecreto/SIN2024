#pragma once

#include "../common.h"

// todo: need more improvement


struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 m_model;

    void update() {
        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, position);

        m_model = glm::rotate(m_model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        m_model = glm::rotate(m_model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        m_model = glm::rotate(m_model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        m_model = glm::scale(m_model, scale);
    }

    Transform() = default;
    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;

        update();
    }

    void setPosition(const glm::vec3& position) {
        this->position = position;
    }

    void setScale(const glm::vec3& scale) {
        this->scale = scale;
    }

    void setRotation(const glm::vec3& rotation) {
        this->rotation = rotation;
    }
};