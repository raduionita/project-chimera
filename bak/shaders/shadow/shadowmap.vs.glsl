#version 420 core

layout (location = 0) in vec4 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;

uniform mat4 u_mMVP;

out vec2 v_vTexcoord;

void main(void) {
  gl_Position = u_mMVP * a_vPosition;
  v_vTexcoord = a_vTexcoord;
}
