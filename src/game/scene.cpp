#include "scene.h"
<<<<<<< HEAD
=======
#include "_camera.h"
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)

std::vector<GameObject> Scene::gameObjects;

Scene::Scene() {
<<<<<<< HEAD
    
=======
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
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}