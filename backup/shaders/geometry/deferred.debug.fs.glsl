#version 420 core

/* @see ogl.hpp */
#define OGL_TEXTURE_GENERIC      0
#define OGL_TEXTURE_DIFFUSE      1
#define OGL_TEXTURE_NORMALS      2
#define OGL_TEXTURE_SPECULAR     3
#define OGL_TEXTURE_DIRECTSHADOW 4
#define OGL_TEXTURE_SPOTSHADOW   5
#define OGL_TEXTURE_POINTSHADOW  6
#define OGL_TEXTURE_ENVIRONMENT  7

in vs_out_t {
  vec3 vPosition;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
} fs_in;

layout (location = 0) out vec4 f_vColor;

layout (binding = OGL_TEXTURE_DIFFUSE) uniform sampler2D u_sDiffuseMap;
layout (binding = OGL_TEXTURE_NORMALS) uniform sampler2D u_sNormalMap;

void main(void) {
  f_vColor = vec4(1.0, 1.0, 0.0, 1.0);
  f_vColor = vec4(texture(u_sDiffuseMap, fs_in.vTexcoord).rgb, 1.0);
  f_vColor = vec4(fs_in.vPosition, 1.0);
}
