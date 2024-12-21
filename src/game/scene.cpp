#include "scene.h"
#include "../clock.hpp"
#include "_camera.h"

Scene::Scene(std::string skyboxPath, std::string skyboxFileFormat)
{
    skybox = Skybox(skyboxPath, skyboxFileFormat);
}

void Scene::add(const GameObject& object) {
    gameObjects.push_back(object);
}

void Scene::addLight(const Light& light) {
    lights.push_back(light);
}

void Scene::render() {
    for (auto& obj : gameObjects) {
        obj.render();
    }
}

void Scene::update() {
    Input::disableCursor();
    Camera::update();
}