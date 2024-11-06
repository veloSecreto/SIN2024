#include "scene.h"
#include "_camera.h"

Scene::Scene() = default;

void Scene::add(const GameObject& object) {
    gameObjects.push_back(object);
}

void Scene::render() {
    update();
    for (auto& obj : gameObjects) {
        obj.render();
    }
}

void Scene::update() {
    Camera::update();
}