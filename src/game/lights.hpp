#include "../common.h"

struct alignas(16) Light {
    glm::vec3 position = glm::vec3(0.0f); float _padding0;
    glm::vec3 color = glm::vec3(1, 0.7799999713897705, 0.5289999842643738);
    float strength = 1.0f;
    float radius = 6.0f; float _padding[3];

    Light() = default;
    Light(const glm::vec3& position, const glm::vec3& color, float strength, float radius) {
        this->position = position;
        this->color = color;
        this->strength = strength;
        this->radius = radius;
    }

    Light(const glm::vec3& position) {
        this->position = position;
    }

    Light(const glm::vec3& position, const glm::vec3& color) {
        this->position = position;
        this->color = color;
    }

    void render();
};