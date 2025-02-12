#version 460 core
in vec3 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main() {
    vec3 fragToLight = FragPos.xyz - lightPos;
    float lightDistance = length(fragToLight);
    lightDistance = lightDistance / far_plane;
    gl_FragDepth = lightDistance;
}