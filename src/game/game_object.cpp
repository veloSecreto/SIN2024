#include "game_object.h"


Model* GameObject::model = nullptr;
Transform GameObject::transform = Transform();
Shader GameObject::shader;

GameObject::GameObject(const std::string& modelName) {
    this->model = AssetManager::getModelByName(modelName);
}

GameObject::GameObject(const std::string& modelName, const std::string& shaderName) {
    this->model = AssetManager::getModelByName(modelName);
    this->shader = OpenGLRenderer::getShaderByName(shaderName);
}

void GameObject::update() {
    transform.update();
}