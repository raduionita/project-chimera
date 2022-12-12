#version 410 core

layout (location = 0) in vec3 a_vPosition;

uniform mat4 u_mMVP;

void main(void) {
  gl_Position = u_mMVP * vec4(a_vPosition, 1.0);
}
