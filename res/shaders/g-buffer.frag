#version 460 core

struct Material {
    sampler2D albedo;
    sampler2D roughness;
    sampler2D metallic;
    sampler2D ao;
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;

layout (location = 1) out vec3 albedo;
layout (location = 2) out vec3 gPosition;
layout (location = 3) out vec3 gNormal;
layout (location = 4) out vec3 rma;

uniform Material material;

float color2float(vec3 c) {
    c *= 255.0;
    c = floor(c);
    return c.r * 256.0 * 256.0 + c.g * 256.0 + c.b - 8388608.0;
}

void main()
{
    albedo.rgb = texture(material.albedo, texCoord).rgb;
    gNormal = normalize(normal);
    gPosition = position;
    rma.r = texture(material.roughness, texCoord).r;
    rma.g = texture(material.metallic, texCoord).r;
    rma.b = texture(material.ao, texCoord).r;
}