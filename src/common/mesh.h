#pragma once

#include "rendererCommon.h"
#include "../api/opengl/gl_backend.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<uint32_t> indices;

    DrawElementsIndirectCommand drawCommand;

    void setupMesh() {
        drawCommand.indexCount = indices.size();
        drawCommand.instancedCount = 1;
        drawCommand.firstIndex = OpenGLBackend::drawCommands.size();
        drawCommand.baseVertex = OpenGLBackend::globalVertices.size();
        drawCommand.baseInstance = 0;

        OpenGLBackend::uploadVertexData(vertices, indices, drawCommand);
    }


    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) {
        this->vertices = vertices;
        this->textures = textures;
        this->indices = indices;

        setupMesh();
    }
};