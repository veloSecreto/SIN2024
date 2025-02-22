#include "game.h"
#include "../core/asset_manager.h"
#include "../file/file_system.h"
#include <random>

void createSceneFromFile();
void createIdoloScene();
void createRandomizedScene();
void createTestScene();

Scene Game::scene;

void Game::init() {
    Camera::init();
    AssetManager::loadAll();
    scene = Scene(ROOT_DIR + "res/skyboxes/Clouds", "jpg");
    createTestScene();
}

void Game::update() {
    scene.update();
}



void createSceneFromFile() {
    Scene& scene = Game::scene;
    auto& sceneData = FileSystem::Repository::getSceneData();
    
    for (unsigned int i = 0; i < sceneData["Game Objects"].size(); i++) {
        auto& data = sceneData["Game Objects"][i];
        GameObject newObj(data["Model Name"]);
        newObj.name = data["Name"];
        newObj.transform.setPosition(glm::vec3(data["Position"][0].get<float>(), data["Position"][1].get<float>(), data["Position"][2].get<float>()));
        newObj.transform.setRotation(glm::vec3(data["Rotation"][0].get<float>(), data["Rotation"][1].get<float>(), data["Rotation"][2].get<float>()));
        newObj.transform.setScale(glm::vec3(data["Scale"][0].get<float>(), data["Scale"][1].get<float>(), data["Scale"][2].get<float>()));
        scene.add(newObj);
    }
    
    for (unsigned int i = 0; i < sceneData["Lights"].size(); i++) {
        auto& data = sceneData["Lights"][i];
        Light newLight;
        newLight.position = glm::vec3(data["Position"][0].get<float>(), data["Position"][1].get<float>(), data["Position"][2].get<float>());
        newLight.color = glm::vec3(data["Color"][0].get<float>(), data["Color"][1].get<float>(), data["Color"][2].get<float>());
        newLight.strength = data["Strength"].get<float>();
        newLight.radius = data["Radius"].get<float>();
        scene.add(newLight);
    }
}

void createIdoloScene() {
    Scene& scene = Game::scene;
    GameObject house("house");
    house.name = "house";
    house.transform.setScale(glm::vec3(0.2f));
    scene.add(house);
    
    GameObject man("nurseGuy");
    man.name = "playboy carti";
    man.transform.setPosition(glm::vec3(0, 0.5f, 4));
    man.transform.setScale(glm::vec3(2));
    scene.add(man);
    
    GameObject obj("mushroom");
    obj.name = "mushroom";
    obj.transform.setPosition(glm::vec3(5, 0.5f, 0));
    scene.add(obj);
    
    scene.add(Light(glm::vec3(5, 3, 0))); // room on the left
    scene.add(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0, 0))); // dinning room light, should be red like my one
    scene.add(Light(glm::vec3(0, 3, 5))); // forward side bed room
}

void createTestScene() {
    Scene& scene = Game::scene;
    
    GameObject plane("cube");
    plane.name = "plane";
    plane.transform.setScale(glm::vec3(10, 0.001, 10));
    plane.transform.setPosition(glm::vec3(0));
    scene.add(plane);

    GameObject cube("cube");
    cube.name = "cube";
    cube.transform.setScale(glm::vec3(0.5));
    scene.add(cube);

    Light light(glm::vec3(0, 5, 0), glm::vec3(1), 5, 10);
    scene.add(light);
}

void createRandomizedScene() {
    Scene& scene = Game::scene;

    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(-10.0f, 10.0f);  // Range for x and z
    std::uniform_real_distribution<float> distY(0.0f, 5.0f);    // Range for y (height)
    std::uniform_real_distribution<float> distColor(0.0f, 1.0f); // Range for light color

    // Add 56 nurseGuy objects with random positions on the x and z axes
    for (int i = 0; i < 56; ++i) {
        GameObject man("nurseGuy");
        man.name = "Object" + std::to_string(i);
        man.transform.setPosition(glm::vec3(dist(gen), distY(gen), dist(gen)));  // Random positions in x, y, z
        man.transform.setScale(glm::vec3(2));
        scene.add(man);
    }

    // Add the mushroom object
    GameObject obj("mushroom");
    obj.transform.setPosition(glm::vec3(4, 0.5f, 0));
    scene.add(obj);

    // Add 1000 lights with random positions and colors
    for (int i = 0; i < 1000; ++i) {
        // Random positions for lights
        glm::vec3 lightPosition(dist(gen), distY(gen), dist(gen));

        // Random color for lights
        glm::vec3 lightColor(distColor(gen), distColor(gen), distColor(gen));
        
        // Add the light to the scene
        scene.add(Light(lightPosition, lightColor, 0.5f, 2.0f));
    }

    // Add fixed lights
    scene.add(Light(glm::vec3(5, 3, 0))); // room on the left
    scene.add(Light(glm::vec3(0, 3, 0), glm::vec3(1, 0.2f, 0.2f))); // dinning room light, should be red like my one
    scene.add(Light(glm::vec3(0, 3, 5))); // forward side bed room
}