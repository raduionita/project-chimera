#version 420 core

layout (location = 0) in vec4  a_vPosition;
layout (location = 1) in vec2  a_vTexcoord;
layout (location = 2) in vec3  a_vNormal;
layout (location = 3) in vec3  a_vTangent;
//layout (location = 4) in ivec3 a_vIdentifier;

//////////////////////////////////////////////////////////////

uniform mat4 u_mM;
uniform mat4 u_mV;
uniform mat4 u_mP;
uniform mat4 u_mMV;
uniform mat4 u_mLightMVP;

layout (std140, binding = 0) uniform model_block {
  mat4 mMatrices[256];
};

// uniform sampler2D u_sTexture;

//////////////////////////////////////////////////////////////

out vs_out_t {
  vec3  vV;
  vec3  vNormal;
  vec2  vTexcoord;
  vec3  vTangent;
  vec4  vLightSpacePos;
  //flat ivec3 vIdentifier;
} vs_out;

void main(void) {
  mat4 mM = mMatrices[gl_InstanceID] * u_mM;

  vs_out.vV             = (mM * a_vPosition).xyz;
  vs_out.vNormal        = mat3(mM) * a_vNormal;
  vs_out.vTexcoord      = a_vTexcoord;
  vs_out.vLightSpacePos = u_mLightMVP * a_vPosition;
  vs_out.vTangent       = mat3(mM) * a_vTangent;
  gl_Position = u_mP * u_mV * mM * a_vPosition;
}

