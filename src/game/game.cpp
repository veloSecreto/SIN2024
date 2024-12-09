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

    GameObject man("nurseGuy", "default");
    man.transform.position = glm::vec3(0, 2, 4);
    scenes["main"].add(man);

    scenes["main"].addLight(Light(glm::vec3(6, 3, 0))); // room on the left
    scenes["main"].addLight(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0.2, 0.2))); // dinning room light, should be red like my one
    scenes["main"].addLight(Light(glm::vec3(0, 3, 6))); // forward side bed room
}

void Game::render() {
    scenes["main"].render();
}