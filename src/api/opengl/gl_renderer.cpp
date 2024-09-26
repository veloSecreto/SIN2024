#include "gl_renderer.h"

namespace OpenGLRenderer {
    uint32_t globalVAO;
    uint32_t globalVBO;
    uint32_t globalEBO;
    uint32_t globalIBO;
    struct Shaders {
        Shader _default;
    } g_shaders;

    void init();
    void render();
    void beginFrame();
    void hotLoadShaders();
    void uploadBuffersToGPU();
    Shader& getDefaultShader();
};


void OpenGLRenderer::hotLoadShaders() {
    std::cout << "Hot Loading Shaders..." << std::endl;
    g_shaders._default.load("default");
}

void OpenGLRenderer::init() {
    hotLoadShaders();
}


void OpenGLRenderer::uploadBuffersToGPU() {
    glGenVertexArrays(1, &globalVAO);

    glGenBuffers(1, &globalVBO);
    glGenBuffers(1, &globalEBO);
    glGenBuffers(1, &globalIBO);

    glBindVertexArray(globalVAO);

    glBindBuffer(GL_ARRAY_BUFFER, globalVBO);
    glBufferData(GL_ARRAY_BUFFER, OpenGLBackend::globalVertices.size() * sizeof(uint32_t), OpenGLBackend::globalVertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, globalEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, OpenGLBackend::globalIndices.size() * sizeof(uint32_t), OpenGLBackend::globalIndices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, globalIBO);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, OpenGLBackend::drawCommands.size() * sizeof(DrawElementsIndirectCommand), OpenGLBackend::drawCommands.data(), GL_DYNAMIC_DRAW);
}

void OpenGLRenderer::render() {

}

void OpenGLRenderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
}

Shader& OpenGLRenderer::getDefaultShader() {
    return g_shaders._default;
}