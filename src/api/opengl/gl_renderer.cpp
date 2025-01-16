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
    g_shaders["lighting"] = new Shader("lighting.vert", "lighting.frag");
    g_shaders["g-buffer"] = new Shader("g-buffer.vert", "g-buffer.frag");
    g_shaders["post-processing"] = new Shader("post-processing.comp");
    g_shaders["light"] = new Shader("light.vert", "light.frag");
    g_shaders["solid_color"] = new Shader("solid_color.vert", "solid_color.frag");
    g_shaders["skybox"] = new Shader("skybox.vert", "skybox.frag");
    g_shaders["screen"] = new Shader("screen.vert", "screen.frag");
    g_shaders["im3d_triangles"] = new Shader("im3d_triangles.vert", "im3d_triangles.frag");
    g_shaders["im3d_lines"] = new Shader("im3d_lines.vert", "im3d_lines.frag", "im3d_lines.geom");
    g_shaders["im3d_points"] = new Shader("im3d_points.vert", "im3d_points.frag");
}

void OpenGLRenderer::onResize()
{
    glViewport(0, 0, Backend::getWinWidth(), Backend::getWinHeight());
    if (Backend::getWinWidth() > 0 || Backend::getWinHeight() > 0)
    {
        Camera::m_proj = Camera::getProjMatrix();
    }
    OpenGLBackend::gbuffer.resize(Backend::getWinWidth(), Backend::getWinHeight());
}

void OpenGLRenderer::onResize(float width, float height)
{
    glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));
    if (width > 0 || height > 0) {
        Camera::m_proj = Camera::getProjMatrix(width, height, FOVY, NEAR_PLANE, FAR_PLANE);
    }
    OpenGLBackend::gbuffer.resize(static_cast<int>(width), static_cast<int>(height));
}

void OpenGLRenderer::hotLoadShaders() {
    std::cout << "Hot Loading Shaders..." << std::endl;
    g_shaders["default"]->load("default.vert", "default.frag");
    g_shaders["lighting"]->load("lighting.vert", "lighting.frag");
    g_shaders["g-buffer"]->load("g-buffer.vert", "g-buffer.frag");
    g_shaders["post-processing"]->load("post-processing.comp");
    g_shaders["light"]->load("light.vert", "light.frag");
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
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);

    std::cout << "All global buffers and Global Vertex Array has been uploaded to the GPU\n";
}

void OpenGLRenderer::renderMesh(DrawElementsIndirectCommand& command) {
    glDrawElementsInstancedBaseVertexBaseInstance(GL_TRIANGLES, command.indexCount, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * command.firstIndex), 1, command.baseVertex, 0);
}

void OpenGLRenderer::beginFrame() {
    glClearColor(BG_COLOR, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    static GBuffer& gbuffer = OpenGLBackend::gbuffer;
    gbuffer.bind();
    beginFrame();
    OpenGLBackend::update();
    if (renderMode == RenderMode::DEFERRED)
    {
        bindVAO();
        Game::render();
        for (const auto& light : Game::scene.lights) {
            light.render();
        }
        Game::scene.skybox.render();
        unbindVAO();
        gbuffer.draw();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    // forward rendering
    else if (renderMode == RenderMode::FORWARD)
    {
        bindVAO();
        Game::render();
        for (const auto& light : Game::scene.lights) {
            light.render();
        }
        Game::scene.skybox.render();
        unbindVAO();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    static Shader* postProcessingShader = OpenGLRenderer::getShaderByName("post-processing");
	postProcessingShader->use();
	glDispatchCompute(
		(Backend::getWinWidth() + 15) / 16,
		(Backend::getWinHeight() + 15) / 16,
		1
	);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    static Shader* shader = g_shaders["screen"];
    shader->use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gbuffer.screen);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBindVertexArray(gbuffer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
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
