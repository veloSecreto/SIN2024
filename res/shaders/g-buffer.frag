/*# version 460 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D screenTexture;

void main()
{
    fragColor = texture(screenTexture, texCoord);
}*/

#version 460 core

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D screenTexture;
vec2 resolution = vec2(800, 600);
uniform float time;

void main()
{
    vec3 color = texture(screenTexture, texCoord).rgb;

    vec3 sepiaColor = vec3(
        dot(color, vec3(0.393, 0.769, 0.189)),
        dot(color, vec3(0.349, 0.686, 0.168)),
        dot(color, vec3(0.272, 0.534, 0.131))
    );
    // vec3 sepiaColor = texture(screenTexture, texCoord).rgb;

    float grain = fract(sin(dot(texCoord * resolution, vec2(12.9898, 78.233)) + time) * 43758.5453123);
    grain = (grain - 0.5) * 0.3; // Adjust intensity (-0.05 to 0.05)
    sepiaColor += vec3(grain);

    vec2 uv = texCoord - vec2(0.5);
    float vignette = smoothstep(0.8, 0.3, length(uv) * 1.5); // Adjust thresholds for intensity
    sepiaColor *= vignette;

    fragColor = vec4(sepiaColor, 1.0);
}
