#include "game_object.h"

// @brief: the fuck I have made
// todo: work more later, first of all complete the rendering system

Model* GameObject::model = nullptr;
Transform GameObject::transform = Transform();

GameObject::GameObject(const std::string& modelName) {
    this->model = AssetManager::getModelByName(modelName);
}

void GameObject::update() {
    transform.update();
}