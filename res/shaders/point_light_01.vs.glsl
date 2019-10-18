#version 420 core

layout (location = 0) in vec4 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;

//////////////////////////////////////////////////////////////

uniform mat4 u_mP;
uniform mat4 u_mMV;

uniform vec3 u_vLightPosition;

//////////////////////////////////////////////////////////////

out vs_out_t {
  vec3 vN;
  vec3 vL;
  vec3 vV;
  vec2 vTexcoord;
} vs_out;

void main(void) {
  vec4 vP = u_mMV * a_vPosition;
  vs_out.vN = mat3(u_mMV) * a_vNormal;
  vs_out.vL = u_vLightPosition - vP.xyz;
  vs_out.vV = vP.xyz;
  vs_out.vTexcoord = a_vTexcoord;
  gl_Position = u_mP * vP;
}
