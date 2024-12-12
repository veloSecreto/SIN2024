#version 460 core

layout (location = 0) in vec3 position;

out vec3 texCoord;

uniform mat4 m_proj;
uniform mat4 m_view;

void main()
{
	texCoord = position;
	gl_Position = (m_proj * m_view * vec4(position, 1.0)).xyww;
}