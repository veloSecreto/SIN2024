#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../input/input.h"
#include "../clock.hpp"


namespace Camera {
    extern glm::vec3 m_position;
    extern glm::vec3 _forward;
    extern glm::vec3 _right;
    extern glm::vec3 _up;

    extern glm::mat4 m_proj;
    extern glm::mat4 m_view;

    extern float pitch;
    extern float yaw;

    extern float speed;

    void init();
    void update();
    void move();
    void rotate();
    void updateVecs();
    const glm::mat4 getViewMatrix();
    const glm::mat4 getProjMatrix();
};
