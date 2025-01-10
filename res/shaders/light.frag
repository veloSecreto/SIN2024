#version 460 core

in vec3 position;

layout (location = 5) out vec4 fragColor;

uniform vec3 color;

void main()
{
    fragColor = vec4(color, 1.0);
}