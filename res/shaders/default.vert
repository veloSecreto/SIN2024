#version 460 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texCoord;

out vec3 position;
out vec3 normal;
out vec2 texCoord;

uniform mat4 m_proj;
uniform mat4 m_view;
uniform mat4 m_model;

void main()
{
    // don't forget to update that
    position = in_position;
    normal = in_normal;
    texCoord = in_texCoord;
    gl_Position = m_proj * m_view * m_model * vec4(in_position, 1.0);
}