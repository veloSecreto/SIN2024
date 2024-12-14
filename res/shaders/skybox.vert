#version 460 core

struct Camera {
    mat4 projection;
    mat4 view;
    vec3 position;
};

layout (std430, binding = 1) buffer CameraBuffer {
    Camera camera;
};

layout (location = 0) in vec3 position;

out vec3 texCoord;

void main()
{
	texCoord = position;
	gl_Position = (camera.projection * mat4(mat3(camera.view)) * vec4(position, 1.0)).xyww;
}