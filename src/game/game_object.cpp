#include "game_object.h"
<<<<<<< HEAD


Model* GameObject::model = nullptr;
Transform GameObject::transform = Transform();

GameObject::GameObject(const std::string& modelName) {
    this->model = AssetManager::getModelByName(modelName);
}

void GameObject::update() {
    Shader shader = OpenGLRenderer::getDefaultShader();
    transform.update();
=======
#include "../api/opengl/gl_renderer.h"

Model* GameObject::model = nullptr;
Transform GameObject::transform = Transform();
Shader GameObject::shader = Shader();

GameObject::GameObject(const std::string& modelName, const std::string& shaderName) {
    this->model = AssetManager::getModelByName(modelName);
    this->shader = OpenGLRenderer::getShaderByName(shaderName);

    shader.setMat4x4("m_proj", Camera::getProjMatrix());
}

void GameObject::render() {
    update();
    shader.use();
    shader.setMat4x4("m_view", Camera::m_view);
    shader.setMat4x4("m_model", transform.to_mat4());
    shader.setMat4x4("m_proj", Camera::getProjMatrix());
    model->render();
}

void GameObject::update() {

>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}