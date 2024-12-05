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

    GameObject house("house", "default");
    house.transform.scale = glm::vec3(0.2);
    scenes["main"].add(house);

    scenes["main"].addLight(Light(glm::vec3(0.0f, 3.0f, 0.0f)));
}

void Game::render() {
    scenes["main"].render();
}