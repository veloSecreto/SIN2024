#pragma once

#include "../common.h"
#include <stb_image/stb_image.h>


// todo: need more improvement

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoord) {
        this->position = position;
        this->normal = normal;
        this->texCoord = texCoord;
    }

    Vertex(glm::vec3 position, glm::vec3 normal) {
        this->position = position;
        this->normal = normal;
    }

    Vertex(glm::vec3 position) {
        this->position = position;
    }

    Vertex() {
        this->position = glm::vec3(0.0f);
        this->normal = glm::vec3(0.0f);
        this->texCoord = glm::vec2(0.0f);
    }
};

struct Texture {
    private:
        uint32_t ID;
        std::string type;
        std::string path;

    public:
        Texture(const std::string& directory, std::string type, std::string path) {
            this->type = type;
            this->path = path;

            int width, height, nrComponents;
            unsigned char* data = stbi_load(directory.c_str(), &width, &height, &nrComponents, 0);

            glGenTextures(1, &this->ID);

            if (data) {
                GLenum format;
                if (nrComponents == 1) {
                    format = GL_RED;
                }
                else if (nrComponents == 3) {
                    format = GL_RGB;
                }
                else if (nrComponents == 4) {
                    format = GL_RGBA;
                }

                glBindTexture(GL_TEXTURE_2D, ID);
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                stbi_image_free(data);
            }
            else {
                std::cout << "Failed to load texture at directory" << directory << std::endl;
                stbi_image_free(data);
            }
        }

        uint32_t& getID() {
            return ID;
        }

        std::string& getPath() {
            return this->path;
        }

        std::string& getType() {
            return this->type;
        }
};

struct DrawElementsIndirectCommand {
    uint32_t indexCount;
    uint32_t instancedCount;
    uint32_t firstIndex;
    uint32_t baseVertex;
    uint32_t baseInstance;
};