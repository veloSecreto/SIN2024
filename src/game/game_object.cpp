#include "game_object.h"
#include "../api/opengl/gl_renderer.h"
#include "../input/input.h"

GameObject::GameObject(const std::string& modelName, const std::string& shaderName) {
    model = AssetManager::getModelByName(modelName);
    shader = OpenGLRenderer::getShaderByName(shaderName);
}

void GameObject::render() {
    update();
    shader->use();
    shader->setMat4x4("m_proj", Camera::m_proj);
    shader->setMat4x4("m_view", Camera::m_view);
    shader->setVec3("camPos", Camera::m_position);
    shader->setMat4x4("m_model", transform.to_mat4());
    shader->setFloat("material.shininess", 32.0f);
    model.render(shader);
}

void GameObject::update() {

}