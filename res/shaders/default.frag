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

struct InstanceData {
    mat4 m_model;
    int albedoID;
    int roughnessID;
    int metallicID;
    int aoID;
};

layout (std430, binding = 0) buffer LightBuffer {
    Light lights[];
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};

layout (std430, binding = 2) buffer InstanceBuffer {
    InstanceData instances[];
};

in vec3 position;
in vec3 normal;
in vec2 texCoord;
in flat int index;

out vec4 fragColor;

const float gamma = 2.4;
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

uniform sampler2DArray textureArray;

void main() {
    InstanceData instance = instances[index];

    vec3 normalDir = normalize(normal);
    vec3 viewDir = normalize(camera.position - position);

    float roughness = texture(textureArray, vec3(texCoord, instance.roughnessID)).r;
    float metallic =  texture(textureArray, vec3(texCoord, instance.metallicID)).r;
    float ao =  texture(textureArray, vec3(texCoord, instance.aoID)).r;
    vec3 albedo = texture(textureArray, vec3(texCoord, instance.albedoID)).rgb;
    albedo = pow(albedo, vec3(gamma));

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    vec3 finalColor = vec3(0.0);
    vec3 GI = albedo * 0.05;

    for (int i = 0; i < lights.length(); ++i) {
        vec3 lightDir = normalize(lights[i].position - position);
        float distance = length(lights[i].position - position);

        float attenuation = 1.0 / (1.0 + distance * distance / (lights[i].radius * lights[i].radius));
        // float attenuation = 1.0 / (distance * distance);

        vec3 H = normalize(viewDir + lightDir);
        float NDF = DistributionGGX(normalDir, H, roughness);
        float G = GeometrySmith(normalDir, viewDir, lightDir, roughness);
        vec3 F = fresnelSchlick(max(dot(H, viewDir), 0.0), F0);

        vec3 nominator = NDF * G * F;
        float denominator = 4.0 * max(dot(normalDir, viewDir), 0.0) * max(dot(normalDir, lightDir), 0.0) + 0.001;
        vec3 specular = nominator / denominator;

        float NdotL = max(dot(normalDir, lightDir), 0.0);
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        vec3 diffuse = kD * albedo / PI;

        vec3 lightContribution = (diffuse + specular) * NdotL * lights[i].color * lights[i].strength * attenuation;

        finalColor += lightContribution;
    }

    finalColor = pow(finalColor + GI, vec3(1 / gamma));
    fragColor = vec4(finalColor * ao, 1.0);
    /*
    vec3 wildColor = vec3(normal.g, normal.r, normal.r);
    wildColor *= wildColor;
    wildColor *= wildColor;
    wildColor += albedo * 0.25;
    fragColor = vec4(wildColor, 1.0);
    */
    fragColor = vec4(1);
}
