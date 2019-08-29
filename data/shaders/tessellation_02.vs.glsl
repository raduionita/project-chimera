#version 420 core

layout (location = 0) in vec3 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;
layout (location = 3) in vec3 a_vTangent;

uniform mat4 u_mMV;
uniform mat4 u_mM;

out vs_out_t {
  vec3 vPosition; // vPosition_MS
  vec2 vTexcoord; // model space
  vec3 vNormal;   // model space
  vec3 vTangent;  // model space
} vs_out;

void main(void) {
  vs_out.vPosition = (u_mM * vec4(a_vPosition, 1.0)).xyz;
  vs_out.vTexcoord = a_vTexcoord;
  vs_out.vNormal   = normalize(mat3(u_mM) * a_vNormal);  // TCS relies on normal being of unit length - otherwise CP
  vs_out.vTangent  = normalize(mat3(u_mM) * a_vTangent); // 
}
