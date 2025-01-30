#pragma once

struct TextureArray {
    unsigned int handle = -1;
    unsigned int slot;
    unsigned int width;
    unsigned int height;
    unsigned int layers;

    TextureArray() = default;
    TextureArray(int _width, int _height, int _layers);
    int getAllocatedSlot(unsigned char* data, int texWidth, int texHeight, int nrComponents);
    void bind(int _slot);

private:
    void resizeImage(unsigned char* data, int width, int height, unsigned char* destData, int destWidth, int destHeight, int components) const;
    void expand(int layers);
};