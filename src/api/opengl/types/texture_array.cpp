#include "texture_array.h"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <cmath>

static GLfloat maxAniso = -1;


TextureArray::TextureArray(int _width, int _height, int _layers) {
    this->width = _width;
    this->height = _height;
    this->layers = _layers;
    this->slot = 0;
    glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &handle);
    glTextureStorage3D(handle, static_cast<int>(1 + std::floor(std::log2(std::max(width, height)))), GL_RGBA8, width, height, layers);

    glTextureParameteri(handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(handle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (maxAniso == -1) glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAniso);
    glTextureParameterf(handle, GL_TEXTURE_MAX_ANISOTROPY, maxAniso);
}

int TextureArray::getAllocatedSlot(unsigned char* data, int texWidth, int texHeight, int nrComponents) {
    if (slot >= layers) {
        expand(layers + 64);
    }

    std::vector<unsigned char> resizedData(width * height * nrComponents);
    if (texWidth != width || texHeight != height) {
        resizeImage(data, texWidth, texHeight, resizedData.data(), width, height, nrComponents);
        data = resizedData.data();
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

    glBindTextureUnit(0, handle);
    glTextureSubImage3D(handle, 0, 0, 0, slot, width, height, 1, format, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(handle);

    return slot++;
}

void TextureArray::bind(int _slot) {
    glBindTextureUnit(_slot, handle);
}

void TextureArray::resizeImage(unsigned char* data, int width, int height, unsigned char* destData, int destWidth, int destHeight, int components) const {
    for (int y = 0; y < destHeight; ++y) {
        for (int x = 0; x < destWidth; ++x) {
            float u = static_cast<float>(x) / (destWidth - 1);
            float v = static_cast<float>(y) / (destHeight - 1);

            int srcX = static_cast<int>(u * (width - 1));
            int srcY = static_cast<int>(v * (height - 1));

            for (int c = 0; c < components; ++c) {
                destData[(y * destWidth + x) * components + c] =
                    data[(srcY * width + srcX) * components + c];
            }
        }
    }
}

void TextureArray::expand(int newLayers) {
    // if (newLayers <= layers) {
    //     std::cerr << "New maxLayers must be greater than current maxLayers." << std::endl;
    //     return;
    // }

    // uint32_t _handle;
    // glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &_handle);
    // glTextureStorage3D(_handle, 1 + std::floor(std::log2(std::max(width, height))), GL_RGBA8, width, height, newLayers);

    // for (int layer = 0; layer < slot; ++layer) {
    //     glCopyImageSubData(handle, GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer,
    //                     _handle, GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer,
    //                     width, height, 1);
    // }

    // glDeleteTextures(1, &handle);
    // handle = _handle;
    // layers = newLayers;

    std::cout << "Expanded texture array to " << layers << " layers." << std::endl;
}
