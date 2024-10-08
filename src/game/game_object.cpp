#include "game_object.h"


Model* GameObject::model = nullptr;
Transform GameObject::transform = Transform();

GameObject::GameObject(const std::string& modelName) {
    this->model = AssetManager::getModelByName(modelName);
}

void GameObject::update() {
    Shader shader = OpenGLRenderer::getDefaultShader();
    transform.update();
}