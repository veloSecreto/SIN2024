#include "textureGenerator.h"
#include "../gl_backend.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>

unsigned int ID;
int index;

uint32_t generateTextureFromPath(const std::string& path) {
	int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    static bool runOnce = true;
    if (runOnce && width == 1024 && height == 1024) {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
        glTexStorage3D(GL_TEXTURE_2D_ARRAY, 5, GL_RGBA8, 1024, 1024, 24);
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

        std::cout << nrComponents << std::endl;
        glBindTexture(GL_TEXTURE_2D_ARRAY, ID);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, 1024, 1024, 1, GL_RGBA, GL_UNSIGNED_BYTE, data); // oh yeah shits working
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        std::cout << "Okkk" << std::endl;
        runOnce = false;
    }

    if (data) {
        stbi_image_free(data);
    }
    else {
        std::cout << "Failed to load texture at directory: " << path << std::endl;
        stbi_image_free(data);
    }

    return index++;
}

uint32_t generateColorTexture(float r, float g, float b) {
    uint32_t tex;
    unsigned char color[4] = {
        static_cast<unsigned char>(r * 255),
        static_cast<unsigned char>(g * 255),
        static_cast<unsigned char>(b * 255),
        255
    };

    // glGenTextures(1, &tex);
    // glBindTexture(GL_TEXTURE_2D, tex);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, color);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}