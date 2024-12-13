#include "game.h"
#include "../core/asset_manager.h"

Scene Game::scene;

void Game::start() {
    Camera::init();
    
    scene = Scene(ROOT_DIR + "res/skyboxes/dark", "png");
    AssetManager::loadAll();

    GameObject house("house", "default");
    house.transform.scale = glm::vec3(0.2f);
    scene.add(house);

    GameObject man("nurseGuy", "default");
    man.transform.position = glm::vec3(0, 0.5f, 4);
    man.transform.scale = glm::vec3(2);
    scene.add(man);

    GameObject obj("mushroom", "default");
    obj.transform.position = glm::vec3(4, 0.5f, 0);
    scene.add(obj);

    scene.addLight(Light(glm::vec3(5, 3, 0))); // room on the left
    scene.addLight(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0.2f, 0.2f))); // dinning room light, should be red like my one
    scene.addLight(Light(glm::vec3(0, 3, 5))); // forward side bed room
}

void Game::render() {
    scene.render();
}