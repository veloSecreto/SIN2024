#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

uniform vec3 light_color;
uniform float time;

void main()
{
    fragColor = vec4(light_color, 0.0);
}

/*
#version 460 core

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

uniform float time;

void main()
{
    float star = smoothstep(0.45, 0.5, fract(texCoord.x * 10.0 + time * 2.0));  // Twinkling effect
    
    vec3 color = vec3(1.0, 0.78, 0.53) * star;
    
    fragColor = vec4(color, 1.0);
}
*/