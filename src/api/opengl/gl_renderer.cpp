#include "gl_renderer.h"
<<<<<<< HEAD

=======
#include "gl_backend.h"
#include "../../game/_camera.h"
#include <filesystem>

// Raw Array and Buffers
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
uint32_t OpenGLRenderer::globalVAO;
uint32_t OpenGLRenderer::globalVBO;
uint32_t OpenGLRenderer::globalEBO;
uint32_t OpenGLRenderer::globalIBO;
<<<<<<< HEAD
=======

>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
std::unordered_map<std::string, Shader> OpenGLRenderer::g_shaders;

void OpenGLRenderer::createShaders() {
    for (const auto& entry : std::filesystem::directory_iterator(ROOT_DIR + "res/shaders")) {
        const std::string name = entry.path().filename().string();
        const std::string key = name.substr(0, name.find_last_of('.'));
        
<<<<<<< HEAD
        g_shaders.emplace(key, Shader());
=======
        if (g_shaders.find(key) == g_shaders.end()) {
            g_shaders.emplace(key, Shader());
            g_shaders[key].load(key);
        }
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
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
<<<<<<< HEAD
    hotLoadShaders();
=======
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}


void OpenGLRenderer::uploadBuffersToGPU() {
    glGenVertexArrays(1, &globalVAO);

<<<<<<< HEAD
    glGenBuffers(1, &globalVBO);
    glGenBuffers(1, &globalEBO);
    glGenBuffers(1, &globalIBO);

    glBindVertexArray(globalVAO);

    glBindBuffer(GL_ARRAY_BUFFER, globalVBO);
    glBufferData(GL_ARRAY_BUFFER, OpenGLBackend::globalVertices.size() * sizeof(Vertex), OpenGLBackend::globalVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, globalEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, OpenGLBackend::globalIndices.size() * sizeof(uint32_t), OpenGLBackend::globalIndices.data(), GL_STATIC_DRAW);

    // glBindBuffer(GL_DRAW_INDIRECT_BUFFER, globalIBO);
    // glBufferData(GL_DRAW_INDIRECT_BUFFER, OpenGLBackend::drawCommands.size() * sizeof(DrawElementsIndirectCommand), OpenGLBackend::drawCommands.data(), GL_STATIC_DRAW);
=======
    bindVAO();

    glGenBuffers(1, &globalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, globalVBO);
    glBufferData(GL_ARRAY_BUFFER, OpenGLBackend::globalVertices.size() * sizeof(Vertex), OpenGLBackend::globalVertices.data(), GL_STATIC_DRAW);
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )0);

<<<<<<< HEAD
    glBindVertexArray(0);
}

void OpenGLRenderer::render(DrawElementsIndirectCommand& command) {
    glBindVertexArray(globalVAO);
    glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, OpenGLBackend::globalIndices.data(), command.instancedCount, command.baseVertex, command.baseInstance);
    glBindVertexArray(0);
=======
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )offsetof(Vertex, texCoord));

    glGenBuffers(1, &globalEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, globalEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, OpenGLBackend::globalIndices.size() * sizeof(uint32_t), OpenGLBackend::globalIndices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &globalIBO);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, globalIBO);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, OpenGLBackend::drawCommands.size() * sizeof(DrawElementsIndirectCommand), OpenGLBackend::drawCommands.data(), GL_STATIC_DRAW);
    
    unbindVAO();
}

void OpenGLRenderer::render(DrawElementsIndirectCommand& command) {
    glDrawElementsInstancedBaseVertex(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, (void*)(command.firstIndex * sizeof(uint32_t)), command.instancedCount, command.baseVertex);
    // glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, (void*)(command.firstIndex * sizeof(uint32_t)), command.instancedCount, command.baseVertex, command.baseInstance);
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}

void OpenGLRenderer::beginFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(BG_COLOR, 1.0f);
}

Shader& OpenGLRenderer::getDefaultShader() {
    return g_shaders.at("default");
}

Shader& OpenGLRenderer::getShaderByName(const std::string& name) {
    return g_shaders.at(name);
<<<<<<< HEAD
=======
}

void OpenGLRenderer::bindVAO() {
    glBindVertexArray(globalVAO);
}

void OpenGLRenderer::unbindVAO() {
    glBindVertexArray(0);
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}