#include "scene.h"
#include "_camera.h"
#include "../api/opengl/gl_backend.h"
#include "../clock.hpp"

Scene::Scene()
{
    skybox = Skybox(ROOT_DIR + "res/skyboxes/dark", "png");
}

void Scene::add(const GameObject& object) {
    gameObjects.push_back(object);
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

void Scene::render() {
    update();
    for (auto& obj : gameObjects) {
        obj.render();
    }

    for (auto& light : lights) {
        light.render();
    }
    skybox.render();
}

void Scene::update() {
    if (Input::mouseButtonDown(SIN_MOUSE_BUTTON_RIGHT)) {
        Input::disableCursor();
        Camera::update();
    }
    else {
        Input::unhideCursor();
    }
    OpenGLBackend::updateSSBObyName("lights", lights.data(), lights.size() * sizeof(Light));
    Light& light = lights[0];
    static glm::vec3 old = light.position;
    float radius = 1.7f;
    float angle = glm::radians(100.0f * Clock::time);
    light.position = old + glm::vec3(radius * glm::sin(angle), 0, radius * glm::cos(angle));
}