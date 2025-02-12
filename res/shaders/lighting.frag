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

in vec2 texCoord;
out vec4 fragColor;

uniform sampler2D albedo;
uniform sampler2D position;
uniform sampler2D normal;
uniform sampler2D rma;
uniform samplerCubeArray shadowMapArray;

const float gamma = 2.4;
const float PI = 3.14159265359;

vec3 fresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float num = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float num = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float ShadowCalculation(int lightIndex, vec3 fragPos, vec3 lightPos)
{
    vec3 fragToLight = fragPos - lightPos;
    float currentDepth = length(fragToLight);
    
    float bias = 0.05;
    float shadow = 0.0;
    int kernelSize = 4;
    float offset = 0.008;

    for (int x = -kernelSize / 2; x < kernelSize / 2; ++x)
    {
        for (int y = -kernelSize / 2; y < kernelSize / 2; ++y)
        {
            vec2 texOffset = vec2(x, y) * offset;
            float closestDepth = texture(shadowMapArray, vec4(fragToLight.xy + texOffset, fragToLight.z, lightIndex)).r;
            closestDepth *= 100;
            shadow += (currentDepth - bias > closestDepth) ? 1.0 : 0.0;
        }
    }

    shadow /= float(kernelSize * kernelSize);
    return 1.0 - shadow;
}

void main() {
    vec3 fragPos = texture(position, texCoord).xyz;
    vec3 normalDir = normalize(texture(normal, texCoord).xyz);
    vec3 viewDir = normalize(camera.position - fragPos);

    float roughness = texture(rma, texCoord).r;
    float metallic = texture(rma, texCoord).g;
    float ao = texture(rma, texCoord).b;

    vec3 diffuseColor = texture(albedo, texCoord).rgb;
    diffuseColor = pow(diffuseColor, vec3(gamma));
    vec3 F0 = mix(vec3(0.04), diffuseColor, metallic);

    vec3 finalColor = vec3(0.0);
    vec3 GI = diffuseColor * 0.01;

    
    for (int i = 0; i < lights.length(); ++i) {
        vec3 lightDir = normalize(lights[i].position - fragPos);
        float distance = length(lights[i].position - fragPos);

        float attenuation = 1.0 / (1.0 + distance * distance / (lights[i].radius * lights[i].radius));

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

        vec3 diffuse = kD * diffuseColor / PI;

        float shadow = ShadowCalculation(i, fragPos, lights[i].position);
        vec3 lightContribution = (diffuse + specular) * NdotL * lights[i].color * lights[i].strength * attenuation * shadow;

        finalColor += lightContribution;
    }

    finalColor = pow(finalColor + GI, vec3(1.0 / gamma));
    fragColor = vec4(finalColor * ao, 1.0);
}
