#include "render_passes.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../gl_renderer.h"
#include "../gl_backend.h"
#include "../../../game/game.h"

void ShadowMapPass() {
    static ShadowMap& shadowMap = OpenGLRenderer::g_shadowMap;
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    
    glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMap.m_ID);
    
    OpenGLRenderer::bindVAO();
    static Shader* depthShader = OpenGLRenderer::g_shaders["shadow pass"];
    static const glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), 1.0f, NEAR_PLANE, FAR_PLANE);
    
    depthShader->use();
    depthShader->setFloat("far_plane", FAR_PLANE);

    for (size_t i = 0; i < Game::scene.lights.size(); i++) {
        Light& light = Game::scene.lights[i];
        
        if (!light.dirty) {
            continue;
        }

        glm::vec3 lightPos = light.position;

        std::vector<glm::mat4> shadowTransforms = {
            shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),  // +X
            shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),  // -X
            shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3( 0.0f,  0.0f,  1.0f)),  // +Y
            shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3( 0.0f,  0.0f, -1.0f)),  // -Y
            shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3( 0.0f, -1.0f,  0.0f)),  // +Z
            shadowProj * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3( 0.0f, -1.0f,  0.0f))   // -Z
        };

        depthShader->setVec3("lightPos", lightPos);
        for (int j = 0; j < 6; j++) {
            depthShader->setMat4x4(("shadowMatrices[" + std::to_string(j) + "]").c_str(), shadowTransforms[j]);
        }

        for (int face = 0; face < 6; ++face) {
            depthShader->setInt("faceIndex", face);
            GLuint layer = i * 6 + face;
            glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap.m_depthTexture, 0, layer);
            glClear(GL_DEPTH_BUFFER_BIT);
            if (!OpenGLBackend::drawCommands.empty()) {
                glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, OpenGLBackend::drawCommands.size(), 0);
            }
        }
        light.dirty = false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}