#include "gl_backend.h"
#include "gl_renderer.h"
#include "../../backend/backend.h"
#include "../../game/game.h"
#include "../../game/_camera.h"

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei /*length*/, const char* message, const void* /*userParam*/) {
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes
    std::cout << "---------------\n";
    std::cout << "Debug message (" << id << "): " << message << "\n";
    switch (source){
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    }
    std::cout << "\n";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    }
    std::cout << "\n";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    }    std::cout << "\n\n\n";
}

std::vector<Vertex>                         OpenGLBackend::globalVertices;
std::vector<Vertex>                         OpenGLBackend::debugVertices;
std::vector<uint32_t>                       OpenGLBackend::globalIndices;
std::vector<DrawElementsIndirectCommand>    OpenGLBackend::drawCommands;
std::unordered_map<std::string, SSBO>       OpenGLBackend::g_ssbos;
std::vector<InstanceData>                   OpenGLBackend::instances;
GBuffer                                     OpenGLBackend::gbuffer;
TextureArray                                OpenGLBackend::g_textureArray;


// struct for passing camera data to ssbo
struct CameraData {
    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 position;
};

void OpenGLBackend::initMinimum() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return;
    }
    glViewport(0, 0, Backend::getWinWidth(), Backend::getWinHeight());
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    std::cout << "\nGPU: " << renderer << "\n";
    std::cout << "GL version: " << major << "." << minor << "\n\n";

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        std::cout << "Debug GL context enabled\n";
    }
    else {
        std::cout << "Debug GL context not available\n";
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLBackend::uploadMeshData(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) {
    globalVertices.insert(globalVertices.end(), vertices.begin(), vertices.end());
    globalIndices.insert(globalIndices.end(), indices.begin(), indices.end());
}

void OpenGLBackend::createSSBOs() {
    g_ssbos["lights"] = SSBO();
    g_ssbos["camera"] = SSBO();
    g_ssbos["instances"] = SSBO();
    std::cout << "SSBO creation process has been completed\n";
}

void OpenGLBackend::uploadSSBOsToGPU() {
    g_ssbos["lights"].create(Game::scene.lights.data(), Game::scene.lights.size() * sizeof(Light), 0);
    // camera
    CameraData cameraData = { Camera::m_proj, Camera::m_view, Camera::m_position };
    g_ssbos["camera"].create(&cameraData, sizeof(CameraData), 1);
    g_ssbos["instances"].create(instances.data(), instances.size() * sizeof(InstanceData), 2);
}

void OpenGLBackend::configureFramebuffers() {
    gbuffer.configure(Backend::getWinWidth(), Backend::getWinHeight());
}

void OpenGLBackend::update() {
    drawCommands.clear();
    instances.clear();
    for (int i = 0; i < Game::scene.gameObjects.size(); ++i) {
        GameObject& gameObject = Game::scene.gameObjects[i];
        gameObject.update();
        InstanceData instance;
        instance.m_model = gameObject.transform.to_mat4();
        for (int j = 0; j < gameObject.model.meshes.size(); ++j) {
            const Mesh& mesh = gameObject.model.meshes[j];
            drawCommands.push_back(mesh.drawCommand);
            instance.albedoIndex = mesh.material.albedo.handle;
            instance.roughnessIndex = mesh.material.roughness.handle;
            instance.metallicIndex = mesh.material.metallic.handle;
            instance.aoIndex = mesh.material.ao.handle;
            instances.push_back(instance);
        }
    }
    static size_t old_size = 0;
    if (drawCommands.size() > old_size) {
        glDeleteBuffers(1, &OpenGLRenderer::globalIBO);
        glGenBuffers(1, &OpenGLRenderer::globalIBO);
        glBindBuffer(GL_DRAW_INDIRECT_BUFFER, OpenGLRenderer::globalIBO);
        glBufferData(GL_DRAW_INDIRECT_BUFFER, OpenGLBackend::drawCommands.size() * sizeof(DrawElementsIndirectCommand), OpenGLBackend::drawCommands.data(), GL_DYNAMIC_DRAW);
        old_size = drawCommands.size();
    }
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, OpenGLRenderer::globalIBO);
    glBufferSubData(GL_DRAW_INDIRECT_BUFFER, 0, drawCommands.size() * sizeof(DrawElementsIndirectCommand), drawCommands.data());

    g_ssbos["lights"].update(Game::scene.lights.data(), Game::scene.lights.size() * sizeof(Light));
    CameraData cameraData = { Camera::m_proj, Camera::m_view, Camera::m_position };
    g_ssbos["camera"].update(&cameraData, sizeof(CameraData));
    g_ssbos["instances"].update(instances.data(), instances.size() * sizeof(InstanceData));
}

void OpenGLBackend::upload() {
    drawCommands.clear();
    instances.clear();
    for (int i = 0; i < Game::scene.gameObjects.size(); ++i) {
        GameObject& gameObject = Game::scene.gameObjects[i];
        gameObject.update();
        InstanceData instance;
        instance.m_model = gameObject.transform.to_mat4();
        for (int j = 0; j < gameObject.model.meshes.size(); ++j) {
            const Mesh& mesh = gameObject.model.meshes[j];
            drawCommands.push_back(mesh.drawCommand);
            instance.albedoIndex = mesh.material.albedo.handle;
            instance.roughnessIndex = mesh.material.roughness.handle;
            instance.metallicIndex = mesh.material.metallic.handle;
            instance.aoIndex = mesh.material.ao.handle;
            instances.push_back(instance);
        }
    }

    createSSBOs();
    uploadSSBOsToGPU();
    configureFramebuffers();
}