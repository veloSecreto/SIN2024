#include "game_object.h"
#include "../api/opengl/gl_renderer.h"
#include "../physics/physics.h"

GameObject::GameObject(const std::string& modelName) {
    _modelName = modelName;
    model = AssetManager::getModelByName(modelName);
    shader = OpenGLRenderer::getShaderByName((OpenGLRenderer::renderMode == RenderMode::FORWARD ? "default" : "g-buffer"));
    // From local to World space coordinates
    aabb = Physics::calculateOBB(model.localAABB, transform);
}

void GameObject::render() {
    update();
    shader->use();
    shader->setMat4x4("m_model", transform.to_mat4());
    model.render(shader);
}

void GameObject::update() {
    if (OpenGLRenderer::_renderModeChanged) {
        shader = OpenGLRenderer::getShaderByName((OpenGLRenderer::renderMode == RenderMode::FORWARD ? "default" : "g-buffer"));
    }

    if (transform.dirty) {
        aabb = Physics::calculateOBB(model.localAABB, transform);
    }
}