@shader GL_VERTEX_SHADER
#version 420 core
// input layout
layout (location = 0) in vec4 a_vPosition;
layout (location = 1) in vec4 a_vTexcoord;

uniform mat4 u_mM;
uniform mat4 u_mV;
uniform mat4 u_mP;
uniform mat4 u_mMVP;

out vec2 v_vTexcoord;

// entry point
void main() {
  gl_Position = u_mMVP * a_vPosition;
  v_vTexcoord = a_vTexcoord.rg;
}

@shader GL_FRAGMENT_SHADER
#version 420 core

@include "feature.hlsl"

#define OGL_TEXTURE_0 0

in vec2 v_vTexcoord;

layout (location = 0) out vec4 f_vColor;

layout (binding = OGL_TEXTURE_0) uniform sampler2D u_sTexture;

void main() {
  f_vColor = vec4(texture(u_sTexture, v_vTexcoord).rgb,1.0);
}
