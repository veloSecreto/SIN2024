#include "game_object.h"
#include "../api/opengl/gl_renderer.h"

Model GameObject::model = Model();
Transform GameObject::transform = Transform();
Shader GameObject::shader = Shader();

GameObject::GameObject(const std::string& modelName, const std::string& shaderName) {
    this->model = AssetManager::getModelByName(modelName);
    this->shader = OpenGLRenderer::getShaderByName(shaderName);

    shader.use();
    shader.setMat4x4("m_proj", Camera::m_proj);
}

void GameObject::render() {
    update();
    shader.use();
    shader.setMat4x4("m_view", Camera::m_view);
    shader.setMat4x4("m_model", transform.to_mat4());
    model.render(shader);
}

void GameObject::update() {

}