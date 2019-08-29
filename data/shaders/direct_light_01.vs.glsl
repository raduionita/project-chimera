#version 420 core

layout (location = 0) in vec3 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;

uniform mat4  u_mM;
uniform mat4  u_mMV;
uniform mat4  u_mP;
uniform float u_fTime = 0.1;

out vec2 v_vTexcoord;
out vec3 v_vNormal;
out vec3 v_vPosition;

void main(void) {
  v_vTexcoord = a_vTexcoord;
  v_vNormal   = (u_mMV * vec4(a_vNormal, 0.0)).xyz;
  v_vPosition = (u_mMV * vec4(v_vPosition, 1.0)).xyz;
  gl_Position = u_mP * u_mMV * vec4(a_vPosition, 1.0);
}
