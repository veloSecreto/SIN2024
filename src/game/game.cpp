#include "game.h"
#include "../core/asset_manager.h"
#include <random>

Scene Game::scene;

void Game::init() {
    Camera::init();
    AssetManager::loadAll();
    scene = Scene(ROOT_DIR + "res/skyboxes/dark", "png");

    GameObject house("house");
    house.transform.setScale(glm::vec3(0.2f));
    scene.add(house);

    GameObject man("nurseGuy");
    man.transform.setPosition(glm::vec3(0, 0.5f, 4));
    man.transform.setScale(glm::vec3(2));
    scene.add(man);

    GameObject obj("mushroom");
    obj.transform.setPosition(glm::vec3(5, 0.5f, 0));
    scene.add(obj);

    GameObject cube("cube");
    cube.transform.setPosition(glm::vec3(0, 1, 0));
    scene.add(cube);

    scene.addLight(Light(glm::vec3(5, 3, 0))); // room on the left
    scene.addLight(Light(glm::vec3(0, 3, 0))); // dinning room light, should be red like my one
    scene.addLight(Light(glm::vec3(0, 3, 5))); // forward side bed room
}

// void Game::init() {
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
//     for (int i = 0; i < 20; ++i) {
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
//     for (int i = 0; i < 500; ++i) {
//         // Random positions for lights
//         glm::vec3 lightPosition(dist(gen), distY(gen), dist(gen));

//         // Random color for lights
//         glm::vec3 lightColor(distColor(gen), distColor(gen), distColor(gen));
        
//         // Add the light to the scene
//         scene.addLight(Light(lightPosition, lightColor, 0.5f, 2.0f));
//     }

//     // Add fixed lights
//     // scene.addLight(Light(glm::vec3(5, 3, 0))); // room on the left
//     // scene.addLight(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0.2f, 0.2f))); // dinning room light, should be red like my one
//     // scene.addLight(Light(glm::vec3(0, 3, 5))); // forward side bed room
// }

// void Game::init() {
//     Camera::init();
//     AssetManager::loadAll();
//     scene = Scene(ROOT_DIR + "res/skyboxes/Clouds", "jpg");

//     for (int i = 0; i < 49; i++) {
//         int col = i % 7;
//         int row = i / 7;
//         const float scale = 0.8f;
//         glm::vec3 position(col - 3.5f, row - 3.5f, -(glm::sin(col * 180 / 7.0f) + glm::sin(row * 180 / 7.0f)) / 2.0f);
//         GameObject obj("sphere");
//         obj.transform.scale = glm::vec3(scale);
//         obj.transform.position = position;
//         scene.add(obj);
//     }

//     GameObject mushroom("mushroom");
//     mushroom.transform.position = glm::vec3(0, 0, 9);
//     scene.add(mushroom);

//     scene.addLight(Light(glm::vec3(-3.5f, -3.5f, 4)));
//     scene.addLight(Light(glm::vec3(-3.5f,  3.5f, 4)));
//     scene.addLight(Light(glm::vec3( 3.5f, -3.5f, 4)));
//     scene.addLight(Light(glm::vec3( 3.5f,  3.5f, 4)));
// }


void Game::render() {
    scene.render();
}

void Game::update() {
    scene.update();
}