#version 460 core

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
};

struct InstanceData {
    mat4 m_model;
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};

layout (std430, binding = 2) buffer InstanceBuffer {
    InstanceData instances[];
};

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

void main()
{
    uint index = gl_DrawID + gl_InstanceID + gl_BaseInstance;
    InstanceData instance = instances[index];
    position = vec3(instance.m_model * vec4(in_position, 1.0));
    normal = normalize(mat3(transpose(inverse(instance.m_model))) * in_normal);
    texCoord = in_texCoord;
    gl_Position = camera.projection * camera.view * instance.m_model * vec4(in_position, 1.0);
}