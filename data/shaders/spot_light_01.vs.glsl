#version 420 core

layout (location = 0) in vec4 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;

//////////////////////////////////////////////////////////////

uniform mat4 u_mP;
uniform mat4 u_mM;
uniform mat4 u_mMV;
uniform mat4 u_mLightMVP;

// uniform sampler2D u_sTexture;

//////////////////////////////////////////////////////////////

out vs_out_t {
  vec3 vN;
  vec3 vV;
  vec2 vTexcoord;
  vec4 vLightSpacePos;
} vs_out;

void main(void) {
  vs_out.vN = mat3(u_mM) * a_vNormal;
  vs_out.vV = (u_mM * a_vPosition).xyz;
  vs_out.vTexcoord = a_vTexcoord;
  vs_out.vLightSpacePos = u_mLightMVP * a_vPosition;
  gl_Position = u_mP * u_mMV * a_vPosition;
}

