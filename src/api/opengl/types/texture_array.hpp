#pragma once

#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <cstdint>
#include <iostream>
#include <algorithm>
#include <vector>

class TextureArray {
public:
    uint32_t ID = 0;
    int nextAvailableLayer = 0;
    int width = 0, height = 0;
    int maxLayers = 124;

    TextureArray() = default;
    TextureArray(int arrayWidth, int arrayHeight, int maxLayers = 124)
        : width(arrayWidth), height(arrayHeight), maxLayers(maxLayers) {
        initialize();
    }

    ~TextureArray() {
        glDeleteTextures(1, &ID);
    }

    int addTexture(unsigned char* data, int texWidth, int texHeight, int nrComponents) {
        if (nextAvailableLayer >= maxLayers) {
            expandLayers(maxLayers + 64);
        }

        if (texWidth != width || texHeight != height) {
            std::vector<unsigned char> resizedData(width * height * nrComponents);
            resizeImage(data, texWidth, texHeight, nrComponents, resizedData.data(), width, height);
            data = resizedData.data();
        }

        // GLenum format = getFormat(nrComponents);
        // if (format == 0) {
        //     return -1;
        // }

        glTextureSubImage3D(ID, 0, 0, 0, nextAvailableLayer, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        // glGenerateTextureMipmap(ID);

        return nextAvailableLayer++;
    }

private:
    void initialize() {
        glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &ID);
        int levels = static_cast<int>(1 + std::floor(std::log2(std::max(width, height))));
        glTextureStorage3D(ID, levels, GL_RGBA8, width, height, maxLayers);

        glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLfloat maxAniso;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY, &maxAniso);
        glTextureParameterf(ID, GL_TEXTURE_MAX_ANISOTROPY, maxAniso);
        
        std::cout << "Initialized texture array: " << maxLayers << " layers, size: " << width << "x" << height << std::endl;
    }

    GLenum getFormat(int components) const {
        switch (components) {
            case 1: return GL_RED;
            case 3: return GL_RGB;
            case 4: return GL_RGBA;
            default:
                std::cerr << "Error: Unsupported number of components: " << components << std::endl;
                return 0;
        }
    }

    void resizeImage(unsigned char* srcData, int srcWidth, int srcHeight, int components,
                     unsigned char* destData, int destWidth, int destHeight) {
        for (int y = 0; y < destHeight; ++y) {
            for (int x = 0; x < destWidth; ++x) {
                float u = static_cast<float>(x) / (destWidth - 1);
                float v = static_cast<float>(y) / (destHeight - 1);

                int srcX = static_cast<int>(u * (srcWidth - 1));
                int srcY = static_cast<int>(v * (srcHeight - 1));

                for (int c = 0; c < components; ++c) {
                    destData[(y * destWidth + x) * components + c] =
                        srcData[(srcY * srcWidth + srcX) * components + c];
                }
            }
        }
    }

    void expandLayers(int newMaxLayers) {
        if (newMaxLayers <= maxLayers) {
            std::cerr << "New maxLayers must be greater than current maxLayers." << std::endl;
            return;
        }

        uint32_t newID;
        glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &newID);
        glTextureStorage3D(newID, 1 + std::floor(std::log2(std::max(width, height))), GL_RGBA8, width, height, newMaxLayers);

        for (int layer = 0; layer < nextAvailableLayer; ++layer) {
            glCopyImageSubData(ID, GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer,
                            newID, GL_TEXTURE_2D_ARRAY, 0, 0, 0, layer,
                            width, height, 1);
        }

        glDeleteTextures(1, &ID);
        ID = newID;
        maxLayers = newMaxLayers;

        std::cout << "Expanded texture array to " << maxLayers << " layers." << std::endl;
    }
};