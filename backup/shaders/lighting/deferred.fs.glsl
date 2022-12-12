#version 420 core

#define EPSILON 0.00001
#define NO_SHADOW -1
#define MAX_DIRECT_LIGHTS 2
#define MAX_SPOT_LIGHTS 10
#define MAX_POINT_LIGHTS 3

// @see ogl.hpp
#define OGL_TEXTURE_GENERIC      0
#define OGL_TEXTURE_DIFFUSE      1
#define OGL_TEXTURE_NORMALS      2
#define OGL_TEXTURE_SPECULAR     3
#define OGL_TEXTURE_POSITIONS    3
#define OGL_TEXTURE_DIRECTSHADOW 4
#define OGL_TEXTURE_SPOTSHADOW   5
#define OGL_TEXTURE_POINTSHADOW  6
#define OGL_TEXTURE_ENVIRONMENT  7
#define OGL_TEXTURE_DEPTH        10

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

struct DirectLight {
  vec3  vColor;
  vec3  vDirection;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  mat4  mVP;
};

struct PointLight {
  vec3  vColor;
  vec3  vPosition;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  float fK0;
  float fK1;
  float fK2;
};

struct SpotLight {
  vec3  vColor;
  vec3  vPosition;
  vec3  vDirection;
  float fCutoff;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  float fK0;
  float fK1;
  float fK2;
  mat4  mVP;
};

struct Material {
  int   iMaps; // has_diffuse, has_normal(bump), has_specular
  vec3  vDiffuseColor;
  float fDiffuseIntensity;
  vec3  vSpecularColor;
  float fSpecularPower;
  float fSpecularIntensity;
};

struct Camera {
  vec3 vPosition;
  mat4 mV;
  mat4 mP;
};

struct Fragment {
  vec3 vPosition;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vColor;
};

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

layout (binding = OGL_TEXTURE_DEPTH)        uniform sampler2D       sDepthMap;
layout (binding = OGL_TEXTURE_NORMALS)      uniform sampler2D       sNormalMap;
layout (binding = OGL_TEXTURE_DIFFUSE)      uniform sampler2D       sColorMap;

layout (binding = OGL_TEXTURE_DIRECTSHADOW) uniform sampler2DShadow sDirectShadowMap;

/* * */ Fragment oFragment;

uniform Camera   oCamera;

uniform DirectLight oDirectLight;

uniform Material oMaterial = { 0, vec3(0), 1.0, vec3(0), 32.0, 0.75 };

uniform float fPcfSize = 1.0;          // default: 1.0 // 
uniform float fPcfStep = 1.0;          // default: 1.0 // @see computeShadowFactor

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

layout (location = 0) out vec4 vColor;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

/**
 * Get texture coordonates - screen space relative
 * @return vec2 Texture coordonate
 */
vec2 computeTexcoord() {
  return gl_FragCoord.xy / textureSize(sDepthMap, 0); //vec2(oRenderer.nWidth, oRenderer.nHeight);
}

/**
 * Compute position using depth buffer - in World Space
 * @param  vec2 Texture coordonates used to sample from Depth Map
 * @return vec3 Position in World Space
 */
vec3 computePosition(in vec2 vTexcoord) {
  vec4 cs;
  cs.xy = vTexcoord * 2.0 - 1.0;
  cs.z  = texture(sDepthMap, vTexcoord).r * 2.0 - 1.0;
  cs.w  = 1.0;
  vec4 hs = inverse(oCamera.mP * oCamera.mV) * cs;
  return hs.xyz / hs.w;
}

/**
 * Gamma correction
 * @param  vec3 vColor
 * @return vec3
 */
vec3 computeGamma(in vec3 vColor) {
  return pow(vColor, vec3(1.0/2.2)); // or 1.0 / 2.2
}

/**
 * PCF Shadow Map Sampling
 * @param  vec4  vPositionLS position if fragment in light space
 * @return float fFactor     [0, 1]
 * @todo   Adjust algorithm to support fPcfSize & fPcfStep fractions
 */
float computeShadowFactor(in sampler2DShadow sShadowMap, in vec4 vPositionLS) {
  // return textureProj(sShadowMap, vPositionLS);  // these 2 behave the same...apparently
  // return shadow2DProj(sShadowMap, vPositionLS);
  vec2 vMapSize = textureSize(sShadowMap, 0); // vec2(640, 480)
  float fFactor = 0.0;
  if(true || vPositionLS.w > 1.0) { // avoid counter shadow
    vec3 vProjCoords = vPositionLS.xyz / vPositionLS.w;
    
    vec3 vTexcoords = 0.5 * vProjCoords + vec3(0.5); // bias
    
    vec2 vOffset = vec2(1.0 / vMapSize.x, 1.0 / vMapSize.y); // how much to move the sample left/right/up/down
    
    // pcf sampling - average around the current sample
    for(float y = -fPcfSize; y <= fPcfSize; y += fPcfStep) { // 1.0
      for(float x = -fPcfSize; x <= fPcfSize; x += fPcfStep) { // 1.0
        fFactor += texture(sShadowMap, vec3(vTexcoords.x + x * vOffset.x, vTexcoords.y + y * vOffset.y, vTexcoords.z + EPSILON));
      }
    }
    
    float fPcfSize2 = (2 * fPcfSize + 1.0);
    fPcfSize2 *= fPcfSize2;                   // no specular hightlights inside shadow
    fFactor = fFactor / fPcfSize2;            // this returns hard shadows w/ soft edges
    
    // fFactor = (0.5 + (fFactor / 9.0) * 0.5); // => [0, 1] // this fucks up lighting, the shadow is too bright
  }
  return fFactor;
}

/**
 * @todo Improve algorithm to support Material colors
 */
vec4 computeDirectLight(in DirectLight oLight, in vec3 vN, in vec3 vPosition) {
  vec3  vL       = -normalize(oLight.vDirection);
  float NdotL    = max(0.0, dot(vN, vL));
  float ambient  = oLight.fAmbientIntensity;
  float diffuse  = NdotL * oLight.fDiffuseIntensity;
  vec3  vV       = normalize(oCamera.vPosition - vPosition);
  vec3  vR       = normalize(reflect(-vL, vN)); // replace by vH computed in vertex shader
  float VdotR    = dot(vV, vR);
  float specular = max(0.0, pow(VdotR, oMaterial.fSpecularPower)) * oMaterial.fSpecularIntensity;
  float fShadow  = computeShadowFactor(sDirectShadowMap, oLight.mVP * vec4(vPosition, 1.0));
  vec3  vResult  = oLight.vColor * min(ambient + fShadow * (diffuse + specular), 1.0);
  vResult = computeGamma(vResult);
  vResult = oFragment.vColor * vResult;
  return vec4(vResult, 1.0);
}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

void main(void) {
  oFragment.vTexcoord = computeTexcoord();
  oFragment.vPosition = computePosition(oFragment.vTexcoord); // texture(sPositionMap, oFragment.vTexcoord).xyz;
  oFragment.vNormal   = normalize(texture(sNormalMap, oFragment.vTexcoord).xyz);
  oFragment.vColor    = texture(sColorMap, oFragment.vTexcoord).rgb;

  vColor = computeDirectLight(oDirectLight, oFragment.vNormal, oFragment.vPosition);
  
  //vColor = vec4(texture(sDepthMap, oFragment.vTexcoord).rgb, 1.0);
  //vColor = vec4(1.0, 0.0, 1.0, 1.0);
}

















