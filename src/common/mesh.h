#pragma once

#include "rendererCommon.h"
#include "../api/opengl/gl_backend.h"
#include "../api/opengl/gl_renderer.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<uint32_t> indices;

    DrawElementsIndirectCommand drawCommand;

    void setup() {
        drawCommand.indexCount = indices.size();
        drawCommand.instancedCount = 1;
        drawCommand.firstIndex = OpenGLBackend::globalIndices.size();
        drawCommand.baseVertex = OpenGLBackend::globalVertices.size();
        drawCommand.baseInstance = 0;
        
        OpenGLBackend::uploadMeshData(vertices, indices, drawCommand);
    }

    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;

        setup();
    }

    void render(Shader* shader) {
        int specularNr = 1;
        int diffuseNr = 1;
        for (int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string name;
            TextureType type = textures[i].getType();
            if (type == TextureType::DIFFUSE) {
                name = "diffuse" + std::to_string(diffuseNr++);
            }
            else if (type == TextureType::SPECULAR) {
                name = "specular" + std::to_string(specularNr++);
            }
            shader->setInt("material." + name, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].getID());
        }
        OpenGLRenderer::render(drawCommand);
    }
};