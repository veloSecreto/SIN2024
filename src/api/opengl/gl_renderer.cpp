#include "gl_renderer.h"

uint32_t OpenGLRenderer::globalVAO;
uint32_t OpenGLRenderer::globalVBO;
uint32_t OpenGLRenderer::globalEBO;
uint32_t OpenGLRenderer::globalIBO;
std::unordered_map<std::string, Shader> OpenGLRenderer::g_shaders;

void OpenGLRenderer::createShaders() {
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/shaders")) {
        const std::string name = entry.path().filename().string();
        const std::string key = name.substr(0, name.find_last_of('.'));
        
        g_shaders.emplace(key, Shader());
    }
}

void OpenGLRenderer::hotLoadShaders() {
    std::cout << "Hot Loading Shaders..." << std::endl;
    for (auto& obj : g_shaders) {
        obj.second.load(obj.first);
    }
}

void OpenGLRenderer::init() {
    createShaders();
    hotLoadShaders();
}


void OpenGLRenderer::uploadBuffersToGPU() {
    glGenVertexArrays(1, &globalVAO);

    glGenBuffers(1, &globalVBO);
    glGenBuffers(1, &globalEBO);
    glGenBuffers(1, &globalIBO);

    glBindVertexArray(globalVAO);

    glBindBuffer(GL_ARRAY_BUFFER, globalVBO);
    glBufferData(GL_ARRAY_BUFFER, OpenGLBackend::globalVertices.size() * sizeof(Vertex), OpenGLBackend::globalVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, globalEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, OpenGLBackend::globalIndices.size() * sizeof(uint32_t), OpenGLBackend::globalIndices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, globalIBO);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, OpenGLBackend::drawCommands.size() * sizeof(DrawElementsIndirectCommand), OpenGLBackend::drawCommands.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )0);

    glBindVertexArray(0);
}

void OpenGLRenderer::render() {
    // bruh it's causing error
    // glBindBuffer(GL_DRAW_INDIRECT_BUFFER, globalIBO);
    glBindVertexArray(globalVAO);
    glMultiDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_INT, ( GLvoid* )0, OpenGLBackend::drawCommands.size(), 0);
    glBindVertexArray(0);
}

void OpenGLRenderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BG_COLOR, 1.0f);
}

Shader& OpenGLRenderer::getDefaultShader() {
    return g_shaders.at("default");
}