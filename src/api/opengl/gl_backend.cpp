#include "gl_backend.h"
#include "../../backend/backend.h"
#include "../../game/game.h"

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
std::vector<uint32_t>                       OpenGLBackend::globalIndices;
std::vector<DrawElementsIndirectCommand>    OpenGLBackend::drawCommands;
std::unordered_map<std::string, SSBO>       OpenGLBackend::g_ssbos;
GBuffer                                     OpenGLBackend::gbuffer;



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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLBackend::uploadMeshData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, DrawElementsIndirectCommand& drawCommand) {
    globalVertices.insert(globalVertices.end(), vertices.begin(), vertices.end());
    globalIndices.insert(globalIndices.end(), indices.begin(), indices.end());
    drawCommands.push_back(drawCommand);
}

void OpenGLBackend::createSSBOs() {
    g_ssbos["lights"] = SSBO();
    std::cout << "SSBO creation process has been completed\n";
}

void OpenGLBackend::uploadSSBOsToGPU() {
    g_ssbos["lights"].create(Game::scenes["main"].lights.data(), Game::scenes["main"].lights.size() * sizeof(Light), 0);
}

void OpenGLBackend::updateSSBObyName(const std::string& name, const void* data, GLsizeiptr size) {
    g_ssbos[name].update(data, size);
}

void OpenGLBackend::configureFBOs() {
    gbuffer.configure(Backend::getWinWidth(), Backend::getWinHeight());
}