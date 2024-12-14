#version 460 core

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

uniform mat4 m_model;

void main()
{
    position = vec3(m_model * vec4(in_position, 1.0));
    normal = normalize(mat3(transpose(inverse(m_model))) * in_normal);
    texCoord = in_texCoord;
    gl_Position = camera.projection * camera.view * m_model * vec4(in_position, 1.0);
}