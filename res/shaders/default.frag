#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 albedo;

struct Material {
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D specular1;
    sampler2D specular2;
};

uniform Material material;

float color2float(vec3 c) {
    c *= 255.0;
    c = floor(c);
    return c.r * 256.0 * 256.0 + c.g * 256.0 + c.b - 8388608.0;
}

void main()
{
    albedo.rgb = texture(material.diffuse1, texCoord).rgb;
    albedo.a = 0.2;
    gNormal = normalize(normal);
    gPosition = position;
}