#version 420 core

layout (location = 0) in vec4  a_vPosition;
layout (location = 1) in vec2  a_vTexcoord;
layout (location = 2) in vec3  a_vNormal;
layout (location = 3) in vec3  a_vTangent;

out vs_out_t {
  vec3  vNormal;
  vec2  vTexcoord;
  vec3  vTangent;
  vec3  vPositionWS;
  vec4  vCurrPositionCS;
  vec4  vPrevPositionCS;
} vs_out;

uniform mat4 u_mCurrM;
uniform mat4 u_mPrevM;
uniform mat4 u_mV;
uniform mat4 u_mP;

void main(void) {
  vs_out.vNormal         = mat3(u_mCurrM) * a_vNormal;
  vs_out.vTexcoord       = a_vTexcoord;
  vs_out.vTangent        = mat3(u_mCurrM) * a_vTangent;
  vs_out.vPositionWS     = (u_mCurrM * a_vPosition).xyz;
  vs_out.vCurrPositionCS = u_mP * u_mV * u_mCurrM * a_vPosition;
  vs_out.vPrevPositionCS = u_mP * u_mV * u_mPrevM * a_vPosition;
  gl_Position            = vs_out.vCurrPositionCS;
}
