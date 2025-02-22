#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <iostream>

struct GBuffer {
    private:
        uint32_t ID = { 0 };
        
    public:
        uint32_t width = { 0 }, height = { 0 };
        
        uint32_t screen = { 0 };
        uint32_t albedo = { 0 };
        uint32_t position = { 0 };
        uint32_t normal = { 0 };
        uint32_t rma = { 0 };
        uint32_t emissive = { 0 };
        uint32_t rbo = { 0 };

        uint32_t VAO;

        void configure(const unsigned int& width, const unsigned int& height);
        void bind() const;
        void draw() const;
        uint32_t& getID();
        void resize(int width, int height);
        void destroy() const;
        ~GBuffer();
};