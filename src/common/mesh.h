#pragma once

#include "rendererCommon.h"
#include "../api/opengl/types/shader.h"

struct Mesh {
    private:
        std::vector<Vertex> vertices;
        std::vector<Texture> textures;
        std::vector<uint32_t> indices;

        DrawElementsIndirectCommand drawCommand;

        void setupMesh() {
            
        }

    public:

        Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures) {
            this->vertices = vertices;
            this->textures = textures;
            this->indices = indices;

            setupMesh();
        }

        void draw(Shader& shader) {
            int specularNr = 1;
            int diffuseNr = 1;

            for (int i = 0; i < textures.size(); i++) {
                glActiveTexture(GL_TEXTURE0 + i);
                std::string number, name;
                name = textures[i].getType();

                if (name == "specular") {
                    number = std::to_string(specularNr++);
                }
                else if (name == "diffuse") {
                    number = std::to_string(diffuseNr++);
                }

                shader.setInt(name + number, i);
                glBindTexture(GL_TEXTURE_2D, textures[i].getID());
            }
        }
};