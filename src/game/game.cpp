#include "game.h"
#include "../core/asset_manager.h"
#include <random>

Scene Game::scene;

void Game::start() {
    Camera::init();
    AssetManager::loadAll();
    scene = Scene(ROOT_DIR + "res/skyboxes/dark", "png");

    GameObject house("house");
    house.transform.scale = glm::vec3(0.2f);
    scene.add(house);

    GameObject man("nurseGuy");
    man.transform.position = glm::vec3(0, 0.5f, 4);
    man.transform.scale = glm::vec3(2);
    scene.add(man);

    GameObject obj("mushroom");
    obj.transform.position = glm::vec3(4, 0.5f, 0);
    scene.add(obj);

    scene.addLight(Light(glm::vec3(5, 3, 0))); // room on the left
    scene.addLight(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0.2f, 0.2f))); // dinning room light, should be red like my one
    scene.addLight(Light(glm::vec3(0, 3, 5))); // forward side bed room
}

// void Game::start() {
//     Camera::init();
//     AssetManager::loadAll();
//     scene = Scene(ROOT_DIR + "res/skyboxes/dark", "png");

//     // Set up random number generation
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<float> dist(-10.0f, 10.0f);  // Range for x and z
//     std::uniform_real_distribution<float> distY(0.0f, 5.0f);    // Range for y (height)
//     std::uniform_real_distribution<float> distColor(0.0f, 1.0f); // Range for light color

//     // Add 56 nurseGuy objects with random positions on the x and z axes
//     for (int i = 0; i < 56; ++i) {
//         GameObject man("nurseGuy");
//         man.transform.position = glm::vec3(dist(gen), distY(gen), dist(gen));  // Random positions in x, y, z
//         man.transform.scale = glm::vec3(2);
//         scene.add(man);
//     }

//     // Add the mushroom object
//     GameObject obj("mushroom");
//     obj.transform.position = glm::vec3(4, 0.5f, 0);
//     scene.add(obj);

//     // Add 1000 lights with random positions and colors
//     for (int i = 0; i < 1; ++i) {
//         // Random positions for lights
//         glm::vec3 lightPosition(dist(gen), distY(gen), dist(gen));

//         // Random color for lights
//         glm::vec3 lightColor(distColor(gen), distColor(gen), distColor(gen));
        
//         // Add the light to the scene
//         scene.addLight(Light(lightPosition, lightColor));
//     }

//     // Add fixed lights
//     scene.addLight(Light(glm::vec3(5, 3, 0))); // room on the left
//     scene.addLight(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0.2f, 0.2f))); // dinning room light, should be red like my one
//     scene.addLight(Light(glm::vec3(0, 3, 5))); // forward side bed room
// }


void Game::render() {
    scene.render();
}

void Game::update() {
    scene.update();
}