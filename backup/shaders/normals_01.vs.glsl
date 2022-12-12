#version 420 core

#define POSITION_ATTRIBUTE 0
#define TEXCOORD_ATTRIBUTE 1
#define NORMAL_ATTRIBUTE   2
#define TANGENT_ATTRIBUTE  3
#define BINORMAL_ATTRIBUTE 4

layout (location = POSITION_ATTRIBUTE) in vec3 a_vPosition;
layout (location = NORMAL_ATTRIBUTE)   in vec3 a_vNormal;
layout (location = TANGENT_ATTRIBUTE)  in vec3 a_vTangent;
layout (location = BINORMAL_ATTRIBUTE) in vec3 a_vBinormal;

uniform mat4 u_mM;
uniform mat4 u_mVP;

out vs_out_t {
  vec3 vPositionWS;
  vec3 vNormalWS;
  vec3 vTangentWS;
  vec3 vBinormalWS;
} vs_out;

void main(void) {
  vs_out.vPositionWS = (u_mM * vec4(a_vPosition, 1.0)).xyz;
  vs_out.vNormalWS   = (u_mM * vec4(a_vNormal, 0.0)).xyz;
  vs_out.vTangentWS  = (u_mM * vec4(a_vTangent, 0.0)).xyz;
  vs_out.vBinormalWS = (u_mM * vec4(a_vBinormal, 0.0)).xyz;
}
