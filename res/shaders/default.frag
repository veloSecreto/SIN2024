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

struct Material {
    sampler2D albedo;
    sampler2D roughness;
    sampler2D metallic;
    sampler2D ao;
};

layout (std430, binding = 0) buffer LightBuffer {
    Light lights[];
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;

out vec4 fragColor;

uniform Material material;

const float gamma = 2.2;
const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

void main() {
    vec3 normalDir = normalize(normal);
    vec3 viewDir = normalize(camera.position - position);

    vec3 albedo = texture(material.albedo, texCoord).rgb;
    vec3 roughness = texture(material.roughness, texCoord).rgb;
    vec3 metallic =  texture(material.metallic, texCoord).rgb;
    vec3 ao =  texture(material.ao, texCoord).rgb;

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 finalColor = vec3(0.0);
    vec3 GI = albedo * ao;

    for (int i = 0; i < lights.length(); ++i) {
        vec3 lightDir = normalize(lights[i].position - position);
        float distance = length(lights[i].position - position);
        float attenuation = 1.0 / (1.0 + distance * distance / (lights[i].radius * lights[i].radius));
        vec3 radiance = lights[i].color * lights[i].strength * attenuation;

        float NDF = DistributionGGX(normalDir, normalize(lightDir + viewDir), roughness.r);
        float G = GeometrySmith(normalDir, viewDir, lightDir, roughness.r);
        vec3 F = fresnelSchlick(max(dot(normalDir, viewDir), 0.0), F0);

        vec3 kD = vec3(1.0) - F;
        kD *= 1.0 - metallic;

        float NdotL = max(dot(normalDir, lightDir), 0.0);
        vec3 diffuse = kD * albedo / PI;
        vec3 specular = (NDF * G * F) / max(4.0 * max(dot(normalDir, viewDir), 0.0) * NdotL, 0.001);

        vec3 lightContribution = (diffuse + specular) * radiance * NdotL;
        finalColor += lightContribution;
    }

    finalColor = pow(finalColor + GI, vec3(1 / gamma));
    fragColor = vec4(finalColor, 1.0);
}
