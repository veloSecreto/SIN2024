#version 460 core

struct InstanceData {
    mat4 m_model;
    int albedoID;
    int roughnessID;
    int metallicID;
    int aoID;
};

layout (std430, binding = 2) buffer InstanceBuffer {
    InstanceData instances[];
};

layout (location = 0) in vec3 position;

uniform mat4 shadowMatrices[6];
uniform int faceIndex;

out vec3 FragPos;

void main() {
    mat4 model = instances[gl_DrawID + gl_InstanceID + gl_BaseInstance].m_model;
    vec4 worldPos = model * vec4(position, 1.0);
    FragPos = worldPos.xyz;
    gl_Position = shadowMatrices[faceIndex] * worldPos;
}