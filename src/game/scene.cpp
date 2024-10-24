#include "scene.h"
#include "_camera.h"

std::vector<GameObject> Scene::gameObjects;

Scene::Scene() {
    Camera::init();
}

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