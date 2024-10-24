#include "_camera.h"
#include "../backend/backend.h"


glm::vec3 Camera::m_position = glm::vec3(0.0f);
glm::vec3 Camera::_forward = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 Camera::_right = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Camera::_up = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 Camera::m_proj = glm::perspective(FOVY, (float)(Backend::getWinWidth() / Backend::getWinHeight()), NEAR_PLANE, FAR_PLANE);
glm::mat4 Camera::m_view = Camera::getViewMatrix();

float Camera::pitch = 0;
float Camera::yaw = 0;

void Camera::init() {
    m_proj = glm::perspective(FOVY, (float)(Backend::getWinWidth() / Backend::getWinHeight()), NEAR_PLANE, FAR_PLANE);
}

void Camera::move() {
    if (Input::keyDown(SIN_KEY_W)) {
        m_position += _forward * Clock::dt * SPEED;
    }
    if (Input::keyDown(SIN_KEY_S)) {
        m_position -= _forward * Clock::dt * SPEED;
    }

    if (Input::keyDown(SIN_KEY_D)) {
        m_position -= _right * Clock::dt * SPEED;
    }
    if (Input::keyDown(SIN_KEY_A)) {
        m_position += _right * Clock::dt * SPEED;
    }

    if (Input::keyDown(SIN_KEY_Q)) {
        m_position -= _up * Clock::dt * SPEED;
    }
    if (Input::keyDown(SIN_KEY_E)) {
        m_position += _up * Clock::dt * SPEED;
    }
}

void Camera::rotate() {
    glm::vec2 mouseRel = Input::getMouseOffset();
    yaw -= mouseRel.x * Input::getMouseSensitivity();
    pitch += mouseRel.y * Input::getMouseSensitivity();
    pitch = std::min(89.0f, std::max(-89.0f, pitch));
    updateVecs();
}

void Camera::update() {
    rotate();
    move();
    m_view = getViewMatrix();
}

void Camera::updateVecs() {
    float _yaw = glm::radians(yaw); 
    float _pitch = glm::radians(pitch);

    _forward.x = glm::cos(_pitch) * glm::cos(_yaw);
    _forward.y = glm::sin(_pitch);
    _forward.z = glm::cos(_pitch) * glm::sin(_yaw);
    _forward = glm::normalize(_forward);

    _right = glm::normalize(glm::cross(_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    _up = glm::normalize(glm::cross(_right, _forward));
}

const glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + _forward, _up);
}

const glm::mat4 Camera::getProjMatrix() {
    return glm::perspective(FOVY, (float)(Backend::getWinWidth() / Backend::getWinHeight()), NEAR_PLANE, FAR_PLANE);
}