#include "skybox.hpp"
#include "shader.h"
#include "../gl_renderer.h"
#include "../../../game/_camera.h"
#include "../../../common/mesh.h"
#include <vector>
#include <stb_image/stb_image.h>

std::vector<Vertex> skyboxVertices = {
    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f)),

    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f,  1.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(0.0f, 0.0f,  1.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f,  1.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(0.0f, 0.0f,  1.0f)),

    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f, 0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f, 0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f, 0.0f,  0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f, 0.0f,  0.0f)),

    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f, 0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f, 0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f, 0.0f,  0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f, 0.0f,  0.0f)),

    Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f, 0.0f)),
    Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f, 0.0f)),

    Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f, 0.0f)),
    Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f, 0.0f)),
    Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f, 0.0f))
};

std::vector<uint32_t> skyboxIndices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4,
    8, 9, 10, 10, 11, 8,
    12, 13, 14, 14, 15, 12,
    16, 17, 18, 18, 19, 16,
    20, 21, 22, 22, 23, 20
};

std::vector<Texture> emptyTextures;
static Mesh skyboxMesh(skyboxVertices, skyboxIndices, emptyTextures);


Skybox::Skybox(const std::string& path, std::string format) {
	std::vector<std::string> faces {
		"right." + format,
		"left." + format,
		"top." + format,
		"bottom." + format,
		"front." + format,
		"back." + format
	};

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

	int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load((path + "/" + faces[i]).c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            std::cout << "Loaded Cubemap texture from path: " << path << "/" << faces[i] << std::endl;
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Failed to load Cubemap texture at path: " << path << "/" << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}


void Skybox::render() {
	glDepthFunc(GL_LEQUAL);
	static Shader* shader = OpenGLRenderer::getShaderByName("skybox");
	shader->use();
	shader->setInt("cubemap", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
	OpenGLRenderer::renderMesh(skyboxMesh.drawCommand);
	glDepthFunc(GL_LESS);
}

uint32_t& Skybox::getID() {
	return ID;
}