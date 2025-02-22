#include "render_passes.h"
#include "../gl_renderer.h"
#include "../gl_backend.h"

void PostProcessingPass() {
    // OpenGLBackend::gbuffer.bind();
    static Shader* shader = OpenGLRenderer::g_shaders["post-processing"];
    glBindImageTexture(0, OpenGLBackend::gbuffer.screen, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA8);
    shader->use();
    glDispatchCompute(
        (OpenGLBackend::gbuffer.width + 7) / 8,
        (OpenGLBackend::gbuffer.height + 7) / 8,
        1
    );
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);
}