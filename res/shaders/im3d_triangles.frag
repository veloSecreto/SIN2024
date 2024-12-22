#version 460 core

struct VertexData {
	float m_edgeDistance;
	float m_size;
	vec4 m_color;
};

in VertexData vData;

out vec4 fResult;
	
void main() 
{
	fResult = vData.m_color;
}