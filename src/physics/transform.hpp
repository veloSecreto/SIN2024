#pragma once

#include "../common.h"

struct Transform {
private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::mat4 modelCache = glm::mat4(1);

    void updateModelCache() {
        modelCache = glm::mat4(1);
        modelCache = glm::translate(modelCache, position);
        modelCache = glm::rotate(modelCache, glm::radians(rotation.z), glm::vec3(0, 0, 1));
        modelCache = glm::rotate(modelCache, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        modelCache = glm::rotate(modelCache, glm::radians(rotation.x), glm::vec3(1, 0, 0));
        modelCache = glm::scale(modelCache, scale);
    }

public:
    bool dirty = true;

    Transform()
        : position(0), rotation(0), scale(1) {
    }

    Transform(const glm::vec3& position)
        : position(position), rotation(0), scale(1) {
    }

    Transform(const glm::vec3& position, const glm::vec3& rotation)
        : position(position), rotation(rotation), scale(1) {
    }

    Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
        : position(position), rotation(rotation), scale(scale) {
    }

    const glm::mat4& to_mat4() {
        if (dirty) {
            updateModelCache();
            dirty = false;
        }
        return modelCache;
    }

    void setPosition(const glm::vec3& position) {
        if (this->position != position) {
            this->position = position;
            dirty = true;
        }
    }

    void setRotation(const glm::vec3& rotation) {
        if (this->rotation != rotation) {
            this->rotation = rotation;
            dirty = true;
        }
    }

    void setScale(const glm::vec3& scale) {
        if (this->scale != scale) {
            this->scale = scale;
            dirty = true;
        }
    }

    const glm::vec3& getPosition() {
        return position;
    }

    const glm::vec3& getRotation() {
        return rotation;
    }

    const glm::vec3& getScale() {
        return scale;
    }
};