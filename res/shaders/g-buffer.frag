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

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D albedo;
uniform float time;
uniform vec3 camPos;

// hope this could be useful, but no

vec3 float2color(float val) {
    val += 8388608.0;
    if (val < 0.0) return vec3(0.0);
    if (val > 16777216.0) return vec3(1.0);
    vec3 c = vec3(0.0);
    c.b = mod(val, 256.0);
    val = floor(val / 256.0);
    c.g = mod(val, 256.0);
    val = floor(val / 256.0);
    c.r = mod(val, 256.0);
    return c / 255.0;
}

void main()
{
    vec3 fragPos = texture(position, texCoord).xyz;
    vec3 normalDir = texture(normal, texCoord).xyz;
    vec3 viewDir = normalize(camPos - fragPos);

    vec3 diffuseColor = texture(albedo, texCoord).rgb;
    vec3 specularColor = vec3(0.2); // texture(albedo, texCoord).aaa;

    vec3 finalColor = vec3(0.0);
    vec3 GI = diffuseColor * 0.15;

    for (int i = 0; i < lights.length(); ++i) {
        Light light = lights[i];

        vec3 lightDir = normalize(light.position - fragPos);
        float distance = length(light.position - fragPos);

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