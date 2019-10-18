#version 420 core

layout (location = 0) in vec3  a_vPosition;
layout (location = 1) in vec2  a_vTexcoord;
layout (location = 2) in vec3  a_vNormal;
layout (location = 3) in vec3  a_vTangent;
//layout (location = 4) in vec3  a_vBinormal;
layout (location = 5) in ivec4 a_vBoneIds;
layout (location = 6) in vec4  a_vBoneWeights;

//TODO: more bones 
// pack 8 ints int ivec4, pack 8 floats into 4 doubles

const uint MAX_BONES = 100;

uniform mat4 u_mM;
uniform mat4 u_mV;
uniform mat4 u_mP;
uniform mat4 u_mB[MAX_BONES];

//layout (std140, binding = 0) uniform model_block {
//  mat4 mMatrices[256];
//};

out vec3 v_vPosition_MS;
out vec2 v_vTexcoord;
out vec3 v_vNormal;  // WS
out vec3 v_vTangent; // WS

void main(void) {
  mat4 mB;
  if(a_vBoneWeights[0] == 0.0) {
    mB = mat4(1.0);
  } else {
    mB = u_mB[a_vBoneIds[0]] * a_vBoneWeights[0]
       + u_mB[a_vBoneIds[1]] * a_vBoneWeights[1]
       + u_mB[a_vBoneIds[2]] * a_vBoneWeights[2]
       + u_mB[a_vBoneIds[3]] * a_vBoneWeights[3]; 
    // + u_mB[a_vBoneIds[3]] * (1.0 - a_vBoneWeights[0] - a_vBoneWeights[1] - a_vBoneWeights[2]);
  }
  
  vec4 vPosition = mB * vec4(a_vPosition, 1.0);     //
  vec4 vNormal   = mB * vec4(a_vNormal,   0.0);
  vec4 vTangent  = mB * vec4(a_vTangent,  0.0);
  
  gl_Position    = u_mP * u_mV * u_mM * vPosition; // clip space
  v_vPosition_MS = (u_mM * vPosition).xyz;         // model space
  v_vTexcoord    = a_vTexcoord;
  v_vNormal      = (u_mM * vNormal).xyz;           // tangent space
  v_vTangent     = (u_mM * vTangent).xyz;          // tangent space
}
