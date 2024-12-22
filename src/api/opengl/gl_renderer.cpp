#include "gl_renderer.h"
#include "gl_backend.h"
#include "../../game/game.h"
#include "../../backend/backend.h"
#include <filesystem>
#include "../../input/input.h"

// Raw Array and Buffers
uint32_t OpenGLRenderer::globalVAO;
uint32_t OpenGLRenderer::globalVBO;
uint32_t OpenGLRenderer::globalEBO;
uint32_t OpenGLRenderer::globalIBO;
uint32_t OpenGLRenderer::debugVAO;
uint32_t OpenGLRenderer::debugVBO;
std::unordered_map<std::string, Shader*> OpenGLRenderer::g_shaders;

// Specs
RenderMode OpenGLRenderer::renderMode;

// shits
bool OpenGLRenderer::_renderModeChanged;
bool OpenGLRenderer::_debugging;


void OpenGLRenderer::createShaders() {
    g_shaders["default"] = new Shader("default.vert", "default.frag");
    g_shaders["lighting"] = new Shader("lighting.comp");
    g_shaders["lighting2"] = new Shader("lighting.vert", "lighting.frag");
    g_shaders["g-buffer"] = new Shader("g-buffer.vert", "g-buffer.frag");
    g_shaders["solid_color"] = new Shader("solid_color.vert", "solid_color.frag");
    g_shaders["skybox"] = new Shader("skybox.vert", "skybox.frag");
    g_shaders["screen"] = new Shader("screen.vert", "screen.frag");
    g_shaders["im3d_triangles"] = new Shader("im3d_triangles.vert", "im3d_triangles.frag");
    g_shaders["im3d_lines"] = new Shader("im3d_lines.vert", "im3d_lines.frag", "im3d_lines.geom");
    g_shaders["im3d_points"] = new Shader("im3d_points.vert", "im3d_points.frag");
}

void OpenGLRenderer::hotLoadShaders() {
    std::cout << "Hot Loading Shaders..." << std::endl;
    g_shaders["default"]->load("default.vert", "default.frag");
    g_shaders["lighting"]->load("lighting.comp");
    g_shaders["lighting2"]->load("lighting.vert", "lighting.frag");
    g_shaders["g-buffer"]->load("g-buffer.vert", "g-buffer.frag");
    g_shaders["solid_color"]->load("solid_color.vert", "solid_color.frag");
    g_shaders["skybox"]->load("skybox.vert", "skybox.frag");
    g_shaders["screen"]->load("screen.vert", "screen.frag");
    g_shaders["im3d_triangles"]->load("im3d_triangles.vert", "im3d_triangles.frag");
    g_shaders["im3d_lines"]->load("im3d_lines.vert", "im3d_lines.frag", "im3d_lines.geom");
    g_shaders["im3d_points"]->load("im3d_points.vert", "im3d_points.frag");
}

void OpenGLRenderer::init() {
    renderMode = RenderMode::FORWARD;
    _renderModeChanged = false;
    createShaders();
}


void OpenGLRenderer::uploadBuffersToGPU() {
    glGenVertexArrays(1, &globalVAO);

    bindVAO();

    glGenBuffers(1, &globalVBO);
    glBindBuffer(GL_ARRAY_BUFFER, globalVBO);
    glBufferData(GL_ARRAY_BUFFER, OpenGLBackend::globalVertices.size() * sizeof(Vertex), OpenGLBackend::globalVertices.data(), GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )offsetof(Vertex, texCoord));

    glGenBuffers(1, &globalEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, globalEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, OpenGLBackend::globalIndices.size() * sizeof(uint32_t), OpenGLBackend::globalIndices.data(), GL_DYNAMIC_DRAW);

    glGenBuffers(1, &globalIBO);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, globalIBO);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, OpenGLBackend::drawCommands.size() * sizeof(DrawElementsIndirectCommand), OpenGLBackend::drawCommands.data(), GL_DYNAMIC_DRAW);
    
    unbindVAO();

    glGenVertexArrays(1, &debugVAO);
    glBindVertexArray(debugVAO);
    glGenBuffers(1, &debugVBO);
    glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
    glBufferData(GL_ARRAY_BUFFER, NULL, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    std::cout << "All global buffers and Global Vertex Array has been uploaded to the GPU\n"; 
}

void OpenGLRenderer::renderMesh(DrawElementsIndirectCommand& command) {
    // glDrawElementsInstancedBaseVertex(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, (void*)(command.firstIndex * sizeof(uint32_t)), command.instancedCount, command.baseVertex);
    // glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * command.firstIndex), 1, command.baseVertex, 0);
    glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * command.firstIndex), 1, command.baseVertex, 0);
}

void OpenGLRenderer::beginFrame() {
    glClearColor(BG_COLOR, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glViewport(0, 0, Backend::getWinWidth(), Backend::getWinHeight());
}

Shader* OpenGLRenderer::getDefaultShader() {
    return g_shaders.at("default");
}

Shader* OpenGLRenderer::getShaderByName(const std::string& name) {
    return g_shaders.at(name);
}

void OpenGLRenderer::bindVAO() {
    glBindVertexArray(globalVAO);
}

void OpenGLRenderer::unbindVAO() {
    glBindVertexArray(0);
}

void OpenGLRenderer::renderFrame() {
    // deferred rendering
    if (renderMode == RenderMode::DEFERRED)
    {
        // geometry pass
        static GBuffer& gbuffer = OpenGLBackend::gbuffer;
        gbuffer.bind();
        beginFrame();
        bindVAO();
        OpenGLBackend::update();
        Game::render();
        unbindVAO();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // lighting pass
        gbuffer.draw();

        // store depth data
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gbuffer.getID());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, Backend::getWinWidth(), Backend::getWinHeight(), 0, 0, Backend::getWinWidth(), Backend::getWinHeight(), GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // pass through
        bindVAO();
        for (auto& light : Game::scene.lights) {
            light.render();
        }
        Game::scene.skybox.render();
        unbindVAO();
    }
    // forward rendering
    else if (renderMode == RenderMode::FORWARD)
    {
        beginFrame();
        bindVAO();
        OpenGLBackend::update();
        Game::render();
        for (auto& light : Game::scene.lights) {
            light.render();
        }
        Game::scene.skybox.render();
        unbindVAO();
    }
}

void OpenGLRenderer::debugAABBs() {
    std::vector<float> vertices;

    static Shader* shader = g_shaders["solid_color"];
    shader->use();
    shader->setVec3("color", glm::vec3(0, 1, 1));
    shader->setMat4x4("m_model", glm::mat4(1));
    glPointSize(3);
    glLineWidth(1);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(debugVAO);
    for (auto& obj : Game::scene.gameObjects) {
        float minX = obj.aabb.min.x, minY = obj.aabb.min.y, minZ = obj.aabb.min.z;
        float maxX = obj.aabb.max.x, maxY = obj.aabb.max.y, maxZ = obj.aabb.max.z;

        vertices.push_back(minX); vertices.push_back(minY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(minY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(minY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(minY); vertices.push_back(maxZ);
        vertices.push_back(maxX); vertices.push_back(minY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(minY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(minY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(minY); vertices.push_back(minZ);

        vertices.push_back(minX); vertices.push_back(maxY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(maxY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(maxY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(maxY); vertices.push_back(maxZ);
        vertices.push_back(maxX); vertices.push_back(maxY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(maxY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(maxY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(maxY); vertices.push_back(minZ);

        vertices.push_back(minX); vertices.push_back(minY); vertices.push_back(minZ);
        vertices.push_back(minX); vertices.push_back(maxY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(minY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(maxY); vertices.push_back(minZ);
        vertices.push_back(maxX); vertices.push_back(minY); vertices.push_back(maxZ);
        vertices.push_back(maxX); vertices.push_back(maxY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(minY); vertices.push_back(maxZ);
        vertices.push_back(minX); vertices.push_back(maxY); vertices.push_back(maxZ);
    }
    glBindBuffer(GL_ARRAY_BUFFER, debugVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
    glDrawArrays(GL_LINES, 0, vertices.size() / 3);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);
}
