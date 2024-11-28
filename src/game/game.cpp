#include "game.h"
#include "../core/asset_manager.h"

std::unordered_map<std::string, Scene> Game::scenes;

void Game::createScene(const std::string& name) {
    scenes[name] = Scene();
}

void Game::start() {
    Camera::init();
    createScene("main");
    AssetManager::loadAll();

    GameObject obj("nurseGuy", "default");
    obj.transform.position = glm::vec3(0.0f, 0.0f, 2.0f);
    scenes["main"].add(obj);
    GameObject a("mushroom", "default");
    a.transform.position = glm::vec3(0.0f, 0.0f, -2.0f);
    scenes["main"].add(a);

    Light light(glm::vec3(0.0f, -2.0f, 0.0f)), light2(glm::vec3(-2.0f, -2.0f, -2.0f));
    scenes["main"].addLight(light);
    scenes["main"].addLight(light2);
}

void Game::render() {
    scenes["main"].render();
}