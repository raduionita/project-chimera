#version 420 core

in vs_out_t {
  vec3  vNormal;
  vec2  vTexcoord;
  vec3  vTangent;
  vec3  vPositionWS;
  vec4  vCurrPositionCS;
  vec4  vPrevPositionCS;
} fs_in;

layout (binding = 0) uniform sampler2D u_sDiffuseMap;
layout (binding = 2) uniform sampler2D u_sNormalsMap;

layout (location = 0) out vec3 f_vColor;
layout (location = 1) out vec2 f_vMotion;

void main(void) {

  vec4 vTotalLight = vec4(1.0); // vTotalLight += computeLight(...)

  f_vColor = (texture(u_sDiffuseMap, fs_in.vTexcoord) * vTotalLight).rgb;
  vec3 vPrevPostionNDC = (fs_in.vPrevPositionCS / fs_in.vPrevPositionCS.w).xyz;
  vec3 vCurrPostionNDC = (fs_in.vCurrPositionCS / fs_in.vCurrPositionCS.w).xyz;
  f_vMotion = (vCurrPostionNDC - vPrevPostionNDC).xy;
}
