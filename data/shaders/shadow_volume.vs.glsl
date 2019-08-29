#version 420 core

layout (location = 0) in vec3 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;

uniform mat4 u_mM;

void main() {
  gl_Position = u_mM * vec4(a_vPosition, 1.0);
}
