#include "_camera.h"
#include "../backend/backend.h"

glm::vec3 Camera::m_position;
glm::vec3 Camera::_forward;
glm::vec3 Camera::_right;
glm::vec3 Camera::_up;

glm::mat4 Camera::m_proj;
glm::mat4 Camera::m_view;

float Camera::pitch;
float Camera::yaw;

float Camera::speed;

void Camera::init() {
    pitch = 0.0f;
    yaw = 90.0f;
    speed = 2.5f;
    m_position = glm::vec3(0.0f);
    updateVecs();
    m_proj = getProjMatrix();
    m_view = getViewMatrix();
}

void Camera::move() {
    if (Input::keyDown(SIN_KEY_W)) {
        m_position += _forward * Clock::dt * speed;
    }
    if (Input::keyDown(SIN_KEY_S)) {
        m_position -= _forward * Clock::dt * speed;
    }
    if (Input::keyDown(SIN_KEY_D)) {
        m_position -= _right * Clock::dt * speed; // matter to fix
    }
    if (Input::keyDown(SIN_KEY_A)) {
        m_position += _right * Clock::dt * speed; // also this one
    }
    if (Input::keyDown(SIN_KEY_Q)) {
        m_position -= _up * Clock::dt * speed;
    }
    if (Input::keyDown(SIN_KEY_E)) {
        m_position += _up * Clock::dt * speed;
    }
}

void Camera::rotate() {
    glm::vec2 mouseRel = Input::getMouseOffset() * Input::getMouseSensitivity();
    yaw -= mouseRel.x;
    pitch += mouseRel.y;
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

    _forward.x = glm::cos(_yaw) * glm::cos(_pitch);
    _forward.y = glm::sin(_pitch);
    _forward.z = glm::sin(_yaw) * glm::cos(_pitch);
    _forward = glm::normalize(_forward);

    _right = glm::normalize(glm::cross(_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
    _up = glm::normalize(glm::cross(_right, _forward));
}

const glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + _forward, _up);
}

const glm::mat4 Camera::getProjMatrix() {
    return glm::perspective(FOVY, (float)Backend::getWinWidth() / (float)Backend::getWinHeight(), NEAR_PLANE, FAR_PLANE);
}