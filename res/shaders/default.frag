#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

struct Material {
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D specular1;
    sampler2D specular2;
};

uniform Material material;

void main()
{
<<<<<<< HEAD
    fragColor = vec4(1.0);
=======
    fragColor = vec4(1.0f);
>>>>>>> d741c32 (Implemented Scene based rendering, has issues)
}