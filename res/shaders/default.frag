#version 460 core

struct Light {
    vec3 position;
    vec3 color;
    float strength;
    float radius;
};

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
};

layout (std430, binding = 0) buffer LightBuffer {
    Light lights[];
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};

layout (std430, binding = 2) buffer TextureSamplerBuffer {
    uvec2 textures[];
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

uniform int diffuseIndex;
uniform int specularIndex;

void main()
{
    vec3 normalDir = normalize(normal);
    vec3 viewDir = normalize(camera.position - position);

    vec3 diffuseColor = texture(sampler2D(textures[diffuseIndex]), texCoord).rgb;
    vec3 specularColor = texture(sampler2D(textures[specularIndex]), texCoord).rgb;

    vec3 finalColor = vec3(0.0);
    vec3 GI = diffuseColor * 0.15;

    for (int i = 0; i < lights.length(); ++i) {
        Light light = lights[i];

        vec3 lightDir = normalize(light.position - position);
        float distance = length(light.position - position);

        float attenuation = 1.0 / (1.0 + distance * distance / (light.radius * light.radius));

        float diff = max(dot(normalDir, lightDir), 0.0);
        vec3 diffuse = light.color * diff * diffuseColor;

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normalDir, halfwayDir), 0.0), 32);
        vec3 specular = light.color * spec * specularColor;

        vec3 lightContribution = (diffuse + specular) * attenuation * light.strength;

        finalColor += lightContribution;
    }

    fragColor = vec4(finalColor + GI, 1.0);
}