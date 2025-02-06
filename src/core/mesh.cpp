#include "mesh.h"
#include "../api/opengl/gl_backend.h"
#include "../api/opengl/gl_renderer.h"
#include "../api/opengl/types/textureGenerator.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {
    drawCommand.indexCount = indices.size();
    drawCommand.instancedCount = 1;
    drawCommand.firstIndex = OpenGLBackend::globalIndices.size();
    drawCommand.baseVertex = OpenGLBackend::globalVertices.size();
    drawCommand.baseInstance = 0;

    OpenGLBackend::uploadMeshData(vertices, indices);
}