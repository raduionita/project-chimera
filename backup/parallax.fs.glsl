#version 420 core

/** @see math.hpp */
#define EPSILON 0.00001

/** @see ogl.hpp */
#define OGL_TEXTURE_DIFFUSE      1
#define OGL_TEXTURE_NORMALS      2

/** @see ogl.hpp */
#define OGL_ATTACHEMENT_COLOR     0
#define OGL_ATTACHEMENT_NORMALS   2
#define OGL_TEXTURE_HEIGHT        11

/** @see CMaterial.hpp */
#define OPTION_NONE         0x0000
#define OPTION_MAP_DIFFUSE  0x0001
#define OPTION_MAP_NORMAL   0x0002
#define OPTION_MAP_HEIGHT   0x0004
#define OPTION_MAP_SPECULAR 0x0008

struct Material {
  int iOptions;
};

in vs_out_t {
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
  vec3 vBinormal;
  
  vec3 vV;
} fs_in;

layout (location = OGL_ATTACHEMENT_NORMALS)   out vec3 o_vNormal;
layout (location = OGL_ATTACHEMENT_COLOR)     out vec3 o_vColor;

layout (binding = OGL_TEXTURE_DIFFUSE) uniform sampler2D u_sDiffuseMap;
layout (binding = OGL_TEXTURE_NORMALS) uniform sampler2D u_sNormalMap;
layout (binding = OGL_TEXTURE_HEIGHT)  uniform sampler2D u_sHeightMap;

uniform float u_fHeightScale = 0.10;

uniform Material u_oMaterial = { OPTION_NONE | OPTION_MAP_DIFFUSE | OPTION_MAP_NORMAL | OPTION_MAP_HEIGHT };

mat3 computeTBN() {
  vec3 vNormal   = normalize(fs_in.vNormal);
  vec3 vTangent  = normalize(fs_in.vTangent);
  vec3 vBinormal = normalize(fs_in.vBinormal);
  return mat3(vTangent, vBinormal, vNormal);
}

vec3 computeNormal(in vec2 vTexcoord) {
  //return normalize(fs_in.vNormal);
  if((u_oMaterial.iOptions & OPTION_MAP_NORMAL) != 0) {
    if((fs_in.vTangent.x < -EPSILON || EPSILON < fs_in.vTangent.x)
    || (fs_in.vTangent.y < -EPSILON || EPSILON < fs_in.vTangent.y)
    || (fs_in.vTangent.z < -EPSILON || EPSILON < fs_in.vTangent.z)) {   // tangent != 0
      // return vec3(1.0); // uncomment to see if tangents work
      
      vec3 vTexel = texture(u_sNormalMap, vTexcoord).xyz;
      
      if((vTexel.x < -EPSILON || EPSILON < vTexel.x)
      || (vTexel.y < -EPSILON || EPSILON < vTexel.y)
      || (vTexel.z < -EPSILON || EPSILON < vTexel.z)) {                 // normal != 0
        // return vec3(1.0); // uncomment to see if normal map works
        
        vec3 vBump     = vTexel * 2.0 - 1.0; // [-1, 1]
        mat3 mTBN      = computeTBN();
        
        return normalize(mTBN * vBump);
      }
    }
  }
  return normalize(fs_in.vNormal);
}

vec2 computeParallax(in vec2 vTexcoord) {
  if((u_oMaterial.iOptions & OPTION_MAP_HEIGHT) != 0) {
    mat3 mTBN = computeTBN();
    vec3 vV   = mTBN * normalize(fs_in.vV);
    
    const float fMinLayers = 16.0;
    const float fMaxLayers = 32.0;
    float fLayers = mix(fMaxLayers, fMinLayers, abs(dot(vec3(0.0, 0.0, 1.0), vV)));
    float fLayerDepth  = 1.0 / fLayers;
    float fCurrLayerDepth = 0.0;
    vec2  vP = vV.xy / vV.z * u_fHeightScale;
    vec2  vDeltaTexcoord = vP / fLayers;                         // step
    vec2  vCurrTexcoord = vTexcoord;
    float fCurrMapDepth = texture(u_sHeightMap, vCurrTexcoord).r;
    
    // layer sampling
    while(fCurrLayerDepth < fCurrMapDepth) {
      vCurrTexcoord   -= vDeltaTexcoord;                         // shift texcoord along P
      fCurrMapDepth    = texture(u_sHeightMap, vCurrTexcoord).r; // get map depth at current texcoord
      fCurrLayerDepth += fLayerDepth;                            // get depth of next layer
    }
    
    // interpolation - as an orientation problem
    //vec2 vPrevTexcoord = vCurrTexcoord + vDeltaTexcoord;
    
    //float fBeforeDepth = texture(u_sHeightMap, vPrevTexcoord).r - fCurrLayerDepth + fLayerDepth;
    //float fAfterDepth  = fCurrMapDepth - fCurrLayerDepth;
    
    //float fWeight = fAfterDepth / (fAfterDepth - fBeforeDepth);
    //vec2  vFinTexcoord = vPrevTexcoord * fWeight + vCurrTexcoord * (1.0 - fWeight); // mix
    
    vec2 vFinTexcoord = vCurrTexcoord;
    
    return vFinTexcoord;
    
    // 1st attempt
    //float fHeight = texture(u_sHeightMap, vTexcoord).r;
    //vec2 vP = (vV.xy / vV.z) * (fHeight * u_fHeightScale);
    //vec2 vResult = vTexcoord - vP;
    //if(vResult.x < 0.0 || 1.0 < vResult.x || vResult.y < 0.0 || 1.0 < vResult.y)
    //  discard;
    // return vResult;
  }
  return vTexcoord;
}

void main(void) {
  vec2 vTexcoord = computeParallax(fs_in.vTexcoord);
  o_vNormal      = computeNormal(vTexcoord);
  o_vColor       = !gl_FrontFacing ? vec3(1.0, 0.0, 0.0) : texture(u_sDiffuseMap, vTexcoord).rgb;
  //o_vColor = vec3(1.0);
}
