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

out vec3 position;

uniform mat4 m_model;

void main()
{
    position = vec3(m_model * vec4(in_position, 1.0));
    gl_Position = camera.projection * camera.view * m_model * vec4(in_position, 1.0);
}