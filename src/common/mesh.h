#pragma once

#include "rendererCommon.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "../api/opengl/types/shader.h"

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<Texture> textures;
    std::vector<uint32_t> indices;

    uint32_t VAO, VBO, EBO;

    Mesh(std::vector<Vertex> vertices, std::vector<Texture> textures, std::vector<uint32_t> indices) {
        this->vertices = vertices;
        this->textures = textures;
        this->indices = indices;

        setupMesh();
    }

    void draw(Shader& shader) {
        
    }

    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )offsetof(Vertex, normal));
        
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), ( void* )offsetof(Vertex, texCoord));

        glBindVertexArray(0);
    }
};