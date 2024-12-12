#version 460 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D albedo;
uniform float time;

void main()
{
    vec3 color = texture(albedo, texCoord).rgb;
    fragColor = vec4(color, 1.0);
}