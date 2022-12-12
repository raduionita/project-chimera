#version 420 core

#define POSITION_ATTRIBUTE 0
#define TEXCOORD_ATTRIBUTE 1
#define NORMAL_ATTRIBUTE   2
#define TANGENT_ATTRIBUTE  3
#define BINORMAL_ATTRIBUTE 4

layout (location = POSITION_ATTRIBUTE) in vec4 a_vPosition;
layout (location = TEXCOORD_ATTRIBUTE) in vec2 a_vTexcoord;
layout (location = NORMAL_ATTRIBUTE)   in vec3 a_vNormal;
layout (location = TANGENT_ATTRIBUTE)  in vec3 a_vTangent;

//////////////////////////////////////////////////////////////

struct Camera {
  vec3 vPosition;
};

//////////////////////////////////////////////////////////////

uniform mat4 u_mM;
uniform mat4 u_mV;
uniform mat4 u_mP;

uniform Camera u_oCamera = { vec3(1.0) };

out vs_out_t {
  vec2 vTexcoord;  
  vec3 vNormal;     // vNormalWS
  vec3 vTangent;    // vTangentWS
  vec3 vBinormal;    // vTangentWS
  
  vec3 vV;
} vs_out;

void main(void) {
  vec4 vPosition     = u_mM * a_vPosition;
  vs_out.vTexcoord   = a_vTexcoord;
  vs_out.vNormal     = normalize((u_mM * vec4(a_vNormal, 0.0)).xyz);
  vs_out.vTangent    = normalize((u_mM * vec4(a_vTangent, 0.0)).xyz);
  vs_out.vBinormal   = cross(vs_out.vNormal, vs_out.vTangent);
  vs_out.vV          = u_oCamera.vPosition - vPosition.xyz; // P -> C // fragment to camera
  
  gl_Position        = u_mP * u_mV * vPosition;
}
