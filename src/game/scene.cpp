#include "scene.h"

std::vector<GameObject> Scene::gameObjects;

Scene::Scene() {
    GameObject object = GameObject();
    gameObjects.push_back(object);
}