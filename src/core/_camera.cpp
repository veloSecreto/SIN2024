#include "_camera.h"
#include "../backend/backend.h"


glm::vec3 Camera::m_position = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::_forward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::_right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Camera::_up = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 Camera::m_proj = Camera::getProjMatrix();
glm::mat4 Camera::m_view = Camera::getViewMatrix();

void Camera::init() {
    // later sometime
}

void Camera::move() {
    if (Input::keyDown(SIN_KEY_W)) {
        m_position += _forward * Clock::dt;
    }
    if (Input::keyDown(SIN_KEY_S)) {
        m_position -= _forward * Clock::dt;
    }

    if (Input::keyDown(SIN_KEY_D)) {
        m_position += _right * Clock::dt;
    }
    if (Input::keyDown(SIN_KEY_A)) {
        m_position -= _right * Clock::dt;
    }

    if (Input::keyDown(SIN_KEY_Q)) {
        m_position += _up * Clock::dt;
    }
    if (Input::keyDown(SIN_KEY_E)) {
        m_position -= _up * Clock::dt;
    }
}

void Camera::rotate() {
    
    updateVecs();
}

void Camera::update() {
    rotate();
    move();
    m_view = getViewMatrix();
}

void Camera::updateVecs() {

}

const glm::mat4& Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + _forward, _up);
}

const glm::mat4& Camera::getProjMatrix() {
    return glm::perspective(FOVY, (float)(Backend::getWinWidth() / Backend::getWinHeight()), NEAR_PLANE, FAR_PLANE);
}