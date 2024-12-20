#include "scene.h"
#include "../clock.hpp"

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
    Light& light = lights[0];
    static glm::vec3 old = light.position;
    float radius = 1.7f;
    float angle = glm::radians(100.0f * Clock::time);
    light.position = old + glm::vec3(radius * glm::sin(angle), 0, radius * glm::cos(angle));
}