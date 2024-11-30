#include "scene.h"
#include "_camera.h"
#include "../api/opengl/gl_backend.h"

Scene::Scene() = default;

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
}

void Scene::update() {
    Camera::update();
    OpenGLBackend::updateSSBObyName("lights", lights.data(), (GLsizeiptr)(lights.size() * sizeof(Light)));
}