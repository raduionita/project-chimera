#version 420 core

layout (location = 0) in vec3 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;
layout (location = 3) in vec3 a_vTangent;

uniform mat4 u_mM;
uniform mat4 u_mV;
uniform mat4 u_mP;

layout (std140, binding = 0) uniform model_block {
  mat4 mMatrices[256];
};

out vs_out_t {
  vec3 vPosition_MS;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
} vs_out;

void main(void) {
  mat4 mM = mMatrices[gl_InstanceID] * u_mM;
  gl_Position = u_mP * u_mV * mM * vec4(a_vPosition, 1.0);
  vs_out.vPosition_MS = (u_mM * vec4(a_vPosition, 1.0)).xyz;
  vs_out.vTexcoord = a_vTexcoord;
  vs_out.vNormal = (u_mM * vec4(a_vNormal, 0.0)).xyz;
  vs_out.vTangent = (u_mM * vec4(a_vTangent, 0.0)).xyz;
}
