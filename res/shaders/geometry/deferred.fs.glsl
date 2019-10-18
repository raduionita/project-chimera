#version 420 core

#define EPSILON 0.00001

/* @see ogl.hpp */
#define OGL_TEXTURE_DIFFUSE      1
#define OGL_TEXTURE_NORMALS      2

#define OGL_ATTACHEMENT_COLOR     0
#define OGL_ATTACHEMENT_NORMALS   2

in vs_out_t {
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
} fs_in;

layout (location = OGL_ATTACHEMENT_NORMALS)   out vec3 o_vNormal;
layout (location = OGL_ATTACHEMENT_COLOR)     out vec3 o_vColor;

layout (binding = OGL_TEXTURE_DIFFUSE) uniform sampler2D u_sDiffuseMap;
layout (binding = OGL_TEXTURE_NORMALS) uniform sampler2D u_sNormalMap;

vec3 computeNormal() {
  //return normalize(fs_in.vNormal);
  if((fs_in.vTangent.x < -EPSILON || EPSILON < fs_in.vTangent.x)
  || (fs_in.vTangent.y < -EPSILON || EPSILON < fs_in.vTangent.y)
  || (fs_in.vTangent.z < -EPSILON || EPSILON < fs_in.vTangent.z)) {   // tangent != 0
    // return vec3(1.0); // uncomment to see if tangents work
    
    vec3 vTexel = texture(u_sNormalMap, fs_in.vTexcoord).xyz;
    
    if((vTexel.x < -EPSILON || EPSILON < vTexel.x)
    || (vTexel.y < -EPSILON || EPSILON < vTexel.y)
    || (vTexel.z < -EPSILON || EPSILON < vTexel.z)) {                 // normal != 0
      // return vec3(1.0); // uncomment to see if normal map works
    
      vec3 vNormal   = normalize(fs_in.vNormal);
      vec3 vTangent  = normalize(fs_in.vTangent);
      // vTangent = normalize(vTangent - dot(vTangent, vNormal) * vNormal); // orthogonalize - already done in object builder
      vec3 vBinormal = cross(vTangent, vNormal);
      vec3 vBump     = vTexel * 2.0 - 1.0;
      mat3 mTBN      = mat3(vTangent, vBinormal, vNormal);
      
      return normalize(mTBN * vBump);
    }
  }
  return normalize(fs_in.vNormal);
}


void main(void) {
  o_vNormal   = computeNormal();
  o_vColor    = texture(u_sDiffuseMap, fs_in.vTexcoord).rgb;
  //o_vColor = vec3(1.0);
}
