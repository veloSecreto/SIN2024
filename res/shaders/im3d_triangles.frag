#version 420

struct VertexData {
	float m_edgeDistance;
	float m_size;
	vec4 m_color;
};

in VertexData vData;
	
layout(location=0) out vec4 fResult;
	
void main() 
{
	fResult = vData.m_color;
}