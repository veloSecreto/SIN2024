#version 460 core

struct VertexData {
	float m_edgeDistance;
	float m_size;
	vec4 m_color;
};

#define kAntialiasing 2.0

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};
	
layout (location = 0) in vec4 aPositionSize;
layout (location = 1) in vec4 aColor;
	
out VertexData vData;
	
void main() 
{
	vData.m_color = aColor.abgr;
	vData.m_color.a *= smoothstep(0.0, 1.0, aPositionSize.w / kAntialiasing);
	
	vData.m_size = max(aPositionSize.w, kAntialiasing);
	gl_Position = camera.projection * camera.view * vec4(aPositionSize.xyz, 1.0);
}