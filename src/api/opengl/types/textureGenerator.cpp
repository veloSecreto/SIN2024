#include "textureGenerator.h"
#include "../gl_backend.h"
#include <stb_image/stb_image.h>
#include <stb_image/stb_image_resize.h>
#include <glad/glad.h>



uint32_t generateTextureFromPath(const std::string& path) {
	int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    int index = -1;

    int resizedSize = 1024 * 1024 * nrComponents;
    unsigned char* resizedData = new unsigned char[resizedSize];
    if (width != 1024 || height != 1024) {
        stbir_resize_uint8(data, width, height, 0, resizedData, 1024, 1024, 0, nrComponents);
        data = resizedData;
    }

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

    if (data) {
        TextureArray& textureArray = OpenGLBackend::g_textureArray;
        if (textureArray.handle == -1) {
            textureArray = TextureArray(1024, 1024, 124);
        }
        index = textureArray.getAllocatedSlot(data, format);
        stbi_image_free(data);
    }
    else {
        std::cout << "Failed to load texture at directory: " << path << std::endl;
        stbi_image_free(data);
    }

    return index;
}

uint32_t generateColorTexture(float r, float g, float b) {
    std::vector<unsigned char> color(1024 * 1024 * 4);
    for (size_t i = 0; i < color.size(); i += 4) {
        color[i]     = static_cast<unsigned char>(r * 255);
        color[i + 1] = static_cast<unsigned char>(g * 255);
        color[i + 2] = static_cast<unsigned char>(b * 255);
        color[i + 3] = 255;
    }

    int index;
    TextureArray& textureArray = OpenGLBackend::g_textureArray;
    if (textureArray.handle == -1) {
        textureArray = TextureArray(1024, 1024, 124);
    }
    index = textureArray.getAllocatedSlot(color.data(), GL_RGBA);
    return index;
}