#version 420 core

layout (location = 0) in vec4 a_vPosition;

void main(void) {
  gl_Position = a_vPosition;
}
