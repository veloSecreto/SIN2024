#include "lights.hpp"

#include "../core/asset_manager.h"
#include "../api/opengl/gl_renderer.h"
#include "../physics/transform.hpp"
#include "_camera.h"
#include "../clock.hpp"


// this function is just for visualization of lights
const void Light::render() const {
    static Mesh sphere = AssetManager::getModelByName("sphere").meshes[0];
    static Shader* shader = OpenGLRenderer::getShaderByName("solid_color");
    Transform transform(position);
    transform.setScale(glm::vec3(0.2f));
    shader->use();
    shader->setMat4x4("m_model", transform.to_mat4());
    shader->setVec3("color", color);
    shader->setFloat("time", Clock::time);
    OpenGLRenderer::renderMesh(sphere.drawCommand);
}