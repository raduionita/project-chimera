#version 420 core

// @see ogl.hpp
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

layout (location = 0) out vec3 o_vPosition;
layout (location = 1) out vec3 o_vNormal;
layout (location = 2) out vec3 o_vDiffuse;

layout (binding = OGL_TEXTURE_DIFFUSE) uniform sampler2D u_sDiffuseMap;
layout (binding = OGL_TEXTURE_NORMALS) uniform sampler2D u_sNormalMap;

vec3 computeNormal() {
  //return normalize(fs_in.vNormal);
  if(fs_in.vTangent == vec3(0.0)) {
    // return vec3(1.0); // uncomment to see if tangents work
    return normalize(fs_in.vNormal);
  }
  vec3 vTexel = texture(u_sNormalMap, fs_in.vTexcoord).xyz;
  if(vTexel == vec3(0.0)) {
    // return vec3(1.0); // uncomment to see if normal map works
    return normalize(fs_in.vNormal);
  }
  
  vec3 vNormal   = normalize(fs_in.vNormal);
  vec3 vTangent  = normalize(fs_in.vTangent);
  // vTangent = normalize(vTangent - dot(vTangent, vNormal) * vNormal); // orthogonalize - already done in object builder
  vec3 vBinormal = cross(vTangent, vNormal);
  vec3 vBump = 2.0 * vTexel - vec3(1.0);
  mat3 mTBN = mat3(vTangent, vBinormal, vNormal);
  return normalize(mTBN * vBump);
  //return normalize(fs_in.vNormal);
}

void main(void) {
  o_vPosition = fs_in.vPosition;
  o_vTexcoord = vec3(fs_in.vTexcoord, 1.0);
  o_vNormal   = computeNormal();
  o_vDiffuse  = texture(u_sDiffuseMap, fs_in.vTexcoord).rgb;
}
