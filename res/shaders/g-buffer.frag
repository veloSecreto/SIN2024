#version 460 core

struct InstanceData {
    mat4 m_model;
    int albedoID;
    int roughnessID;
    int metallicID;
    int aoID;
};

layout (std430, binding = 2) buffer InstanceBuffer {
    InstanceData instances[];
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in flat int index;

layout (location = 1) out vec3 albedo;
layout (location = 2) out vec3 gPosition;
layout (location = 3) out vec3 gNormal;
layout (location = 4) out vec3 rma;

uniform sampler2DArray textureArray;

float color2float(vec3 c) {
    c *= 255.0;
    c = floor(c);
    return c.r * 256.0 * 256.0 + c.g * 256.0 + c.b - 8388608.0;
}

void main()
{
    InstanceData instance = instances[index];
    albedo.rgb = texture(textureArray, vec3(texCoord, instance.albedoID)).rgb;
    gNormal = normalize(normal);
    gPosition = position;
    rma.r = texture(textureArray, vec3(texCoord, instance.roughnessID)).r;
    rma.g = texture(textureArray, vec3(texCoord, instance.metallicID)).r;
    rma.b = texture(textureArray, vec3(texCoord, instance.aoID)).r;
}