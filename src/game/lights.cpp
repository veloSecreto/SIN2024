#include "lights.hpp"

#include "../core/asset_manager.h"
#include "../api/opengl/gl_renderer.h"
#include "../common/types.h"
#include "_camera.h"
#include "../clock.hpp"

void Light::render() {
    Shader* shader = OpenGLRenderer::getShaderByName("pass_through");
    Transform transform(position);
    transform.scale = glm::vec3(0.2f);
    shader->use();
    shader->setMat4x4("m_proj", Camera::m_proj);
    shader->setMat4x4("m_view", Camera::m_view);
    shader->setMat4x4("m_model", transform.to_mat4());
    shader->setVec3("light_color", color);
    shader->setFloat("time", Clock::time);
    AssetManager::getModelByName("sphere").render(shader);
}