#version 420 core

layout (location = 0) in vec3 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;

uniform mat4  u_mMV;
uniform mat4  u_mP;
uniform float u_fTime = 0.1;

out vec2 v_vTexcoord;

void main(void) {
  v_vTexcoord = a_vTexcoord;
  gl_Position = u_mP * u_mMV * vec4(a_vPosition, 1.0);
}
