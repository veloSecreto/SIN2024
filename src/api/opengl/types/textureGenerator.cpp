#include "textureGenerator.h"
#include "../gl_backend.h"
#include <stb_image/stb_image.h>
#include <glad/glad.h>


uint32_t generateTextureFromPath(const std::string& path) {
    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    if (!data) {
        std::cerr << "Failed to load texture at path: " << path << std::endl;
        return 0;
    }
    
    if (width <= 0 || height <= 0 || nrComponents <= 0) {
        std::cerr << "Invalid dimensions or components for texture at path: " << path << std::endl;
        stbi_image_free(data);
        return 0;
    }

    int index = OpenGLBackend::textureArray.addTexture(data, width, height, nrComponents);
    stbi_image_free(data);
    return index;
}

uint32_t generateColorTexture(float r, float g, float b) {
    unsigned char color[4] = {
        static_cast<unsigned char>(r * 255),
        static_cast<unsigned char>(g * 255),
        static_cast<unsigned char>(b * 255),
        255
    };
    int index = OpenGLBackend::textureArray.addTexture(color, 1024, 1024, 4);
    return index;
}