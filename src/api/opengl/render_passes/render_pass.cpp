#include "render_passes.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../gl_renderer.h"
#include "../gl_backend.h"
#include "../../../game/game.h"

void RenderPass() {
    // deferred rendering
    static GBuffer& gbuffer = OpenGLBackend::gbuffer;
    gbuffer.bind();
    OpenGLRenderer::beginFrame();
    OpenGLRenderer::bindVAO();
    if (OpenGLRenderer::renderMode == RenderMode::DEFERRED)
    {
        static Shader* shader = OpenGLRenderer::g_shaders["g-buffer"];
        shader->use();
        OpenGLBackend::g_textureArray.bind(0);
        shader->setInt("shadowMapArray", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, OpenGLRenderer::g_shadowMap.m_depthTexture);
        glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, OpenGLBackend::drawCommands.size(), 0);
        // the gbuffer needs to be drawn by itself, so unbind the vao once and rebind it again after finishing drawing
        OpenGLRenderer::unbindVAO();
        gbuffer.draw();
        OpenGLRenderer::bindVAO();
    }
    // forward rendering
    else if (OpenGLRenderer::renderMode == RenderMode::FORWARD)
    {
        static Shader* shader = OpenGLRenderer::g_shaders["default"];
        shader->use();
        OpenGLBackend::g_textureArray.bind(0);
        glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, OpenGLBackend::drawCommands.size(), 0);
    }

    // Game::scene.skybox.render();
    for (const auto& light : Game::scene.lights) {
        light.render();
    }
    OpenGLRenderer::unbindVAO();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}