#define GL_VERTEX_SHADER
#version 420 core

layout (location = 0) in vec4 a_vPosition;

uniform mat4 u_mMVP;

void main(void) {
  gl_Position = u_mMVP * a_vPosition;
}

#define GL_FRAGMENT_SHADER
