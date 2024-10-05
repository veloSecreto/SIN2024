#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

struct Material {
    uniform mat4 diffuse1;
    uniform mat4 diffuse2;
    uniform mat4 specular1;
    uniform mat4 specular2;
};

void main()
{
    fragColor = vec4(1.0);
}