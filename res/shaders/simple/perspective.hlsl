@shader GL_VERTEX_SHADER
#version 420 core
// input layout
layout (location = 0) in vec4 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;
//layout (location = 3) in int a_nColor;
//layout (location = 4) in vec3 a_vTangent;
//layout (location = 5) in vec3 a_vBinormal;
//layout (location = 6) in ivec3 a_vJoints;
//layout (location = 7) in vec3 a_vWeights;

uniform mat4 u_mM;
uniform mat4 u_mV;
uniform mat4 u_mP;
uniform mat4 u_mPVM;


out vec2 v_vTexcoord;
out vec3 v_vNormal;

// entry point
void main() {
  gl_Position = u_mPVM * a_vPosition;
  v_vTexcoord = a_vTexcoord;
  v_vNormal   = a_vNormal;
}

@shader GL_FRAGMENT_SHADER
#version 420 core

@include "feature.hlsl"

#define OGL_TEXTURE_0 0

in vec2 v_vTexcoord;
in vec3 v_vNormal;

layout (location = 0) out vec4 f_vColor;

layout (binding = OGL_TEXTURE_0) uniform sampler2D u_sTexture;

void main() {
  f_vColor = vec4(texture(u_sTexture, v_vTexcoord.rg).rgb,1.0);
}
