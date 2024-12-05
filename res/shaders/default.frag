#version 460 core

struct Light {
    vec3 position;
    vec3 color;
    float strength;
    float radius;
};

layout (std430, binding = 0) buffer LightBuffer {
    Light lights[];
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

struct Material {
    sampler2D diffuse1;
    sampler2D diffuse2;
    sampler2D specular1;
    sampler2D specular2;
    float shininess;
};


uniform Material material;
uniform vec3 camPos;

void main()
{
    vec3 normalDir = normalize(normal);
    vec3 viewDir = normalize(camPos - position);

    vec3 diffuseColor = texture(material.diffuse1, texCoord).rgb;
    vec3 specularColor = texture(material.specular1, texCoord).rgb;

    vec3 finalColor = vec3(0.0);
    vec3 GI = vec3(0);

    for (int i = 0; i < lights.length(); ++i) {
        Light light = lights[i];

        vec3 lightDir = normalize(light.position - position);
        float distance = length(light.position - position);

        float attenuation = 1.0 / (1.0 + distance * distance / (light.radius * light.radius));

        float diff = max(dot(normalDir, lightDir), 0.0);
        vec3 diffuse = light.color * diff * diffuseColor;

        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(normalDir, halfwayDir), 0.0), material.shininess);
        vec3 specular = light.color * spec * specularColor;

        vec3 lightContribution = (diffuse + specular) * attenuation * light.strength;

        finalColor += lightContribution;
    }
    fragColor = vec4(finalColor + GI, 1.0);
}