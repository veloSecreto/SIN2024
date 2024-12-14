#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

layout (location = 0) out vec4 albedo;
layout (location = 1) out vec3 gPosition;
layout (location = 2) out vec3 gNormal;

uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;

float color2float(vec3 c) {
    c *= 255.0;
    c = floor(c);
    return c.r * 256.0 * 256.0 + c.g * 256.0 + c.b - 8388608.0;
}

void main()
{
    albedo.rgb = texture(diffuseTexture, texCoord).rgb;
    albedo.a = 0.2;
    gNormal = normalize(normal);
    gPosition = position;
}