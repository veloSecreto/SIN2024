#pragma once
#include <vector>

struct ShadowMap {
    void init(unsigned int numberOfCubemaps);
    void cleanUp();
    void bind();
    unsigned int getDepthTexture() const { return m_depthTexture; }
    unsigned int getTextureView() const { return m_textureView; }
    ShadowMap() = default;
    ~ShadowMap() { cleanUp(); }

    unsigned int m_ID = 0;
    unsigned int m_depthTexture = 0;
    unsigned int m_numberOfCubemaps = 0;
    unsigned int m_textureView = 0;
};