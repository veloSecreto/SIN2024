#pragma once

#include "rendererCommon.h"
#include "../api/opengl/gl_backend.h"
#include "../api/opengl/gl_renderer.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<uint32_t> indices;

    DrawElementsIndirectCommand drawCommand;

    void setupMesh() {
        drawCommand.indexCount = indices.size();
        drawCommand.instancedCount = 1;
<<<<<<< HEAD
        drawCommand.firstIndex = OpenGLBackend::drawCommands.size();
=======
        drawCommand.firstIndex = OpenGLBackend::globalIndices.size();
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
        drawCommand.baseVertex = OpenGLBackend::globalVertices.size();
        drawCommand.baseInstance = 0;

        OpenGLBackend::uploadMeshData(vertices, indices, drawCommand);
    }

<<<<<<< HEAD

=======
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setupMesh();
    }

    void render() {
        OpenGLRenderer::render(drawCommand);
    }
};