#pragma once

#include "../common.h"

struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 to_mat4() const {
        glm::mat4 m_model(1.0f);
        m_model = glm::translate(m_model, position);
        m_model = glm::rotate(m_model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        m_model = glm::rotate(m_model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        m_model = glm::rotate(m_model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        m_model = glm::scale(m_model, scale);
        return m_model;
    }

    Transform()
        : position(0.0f), rotation(0), scale(1.0f) {}

    Transform(const glm::vec3& position)
        : position(position), rotation(0), scale(1.0f) {}

    Transform(const glm::vec3& position, const glm::vec3& rotation)
        : position(position), rotation(rotation), scale(1.0f) {}

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position), rotation(rotation), scale(scale) {}
};