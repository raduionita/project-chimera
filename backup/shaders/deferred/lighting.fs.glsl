#version 420 core

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
};

struct Scene {
  uint nDirectLights;
  uint nPointLights;
  uint nSpotLights;
};

struct Renderer {
  uint nWidth;
  uint nHeight;
};

struct Fragment {
  vec3 vPosition;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vColor;
};

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

/* * */ Fragment oFragment;

layout (binding = OGL_TEXTURE_POSITIONS) uniform sampler2D sPositionMap;
layout (binding = OGL_TEXTURE_NORMALS)   uniform sampler2D sNormalMap;
layout (binding = OGL_TEXTURE_DIFFUSE)   uniform sampler2D sColorMap;

uniform Scene    oScene;
uniform Camera   oCamera;
uniform Renderer oRenderer;

uniform DirectLight oDirectLights[1];
uniform PointLight  oPointLight;
uniform SpotLight   oSpotLights[99];

uniform Material oMaterial = { 0, vec3(0), 1.0, vec3(0), 0.75, 32.0 };

uniform float fPcfSize = 1.0;          // default: 1.0 // 
uniform float fPcfStep = 1.0;          // default: 1.0 // @see computeShadowFactor

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

layout (location = 0) out vec4 f_vColor;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

/**
 * @return vec2
 */
vec2 computeTexcoord() {
  return gl_FragCoord.xy / vec2(oRenderer.nWidth, oRenderer.nHeight);
}

/**
 * Gamma correction
 * @param  vec3 vColor
 * @return vec3
 */
vec3 computeGamma(in vec3 vColor) {
  return pow(vColor, vec3(2.2)); // or 1.0 / 2.2
}

/**
 * @todo Improve algorithm to support Material colors
 */
vec4 computeDirectLight(in DirectLight oLight, in vec3 vN, in vec3 vPosition) {
  vec3  vL = -normalize(oLight.vDirection);
  float NdotL = max(0.0, dot(vN, vL));
  float ambient = oLight.fAmbientIntensity;
  float diffuse = NdotL * oLight.fDiffuseIntensity;
  vec3  vV = normalize(oCamera.vPosition - vPosition);
  vec3  vR = normalize(reflect(-vL, vN)); // replace by vH
  float VdotR = dot(vV, vR);
  float specular = NdotL <= 0.0 ? 0.0 : max(0.0, pow(VdotR, oMaterial.fSpecularPower)) * oMaterial.fSpecularIntensity;
  float fShadow  = 1.0f; // computeShadowFactor(sDirectShadowMap, oLight.mVP * vec4(vPosition, 1.0));
  vec3  vResult = oLight.vColor * min(ambient + fShadow * (diffuse + specular), 1.0);
  vResult = computeGamma(vResult);
  return vec4(vResult, 1.0);
}

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

void main(void) {
  vec2 vTexcoord = computeTexcoord();
  vec3 vPosition = texture(sPositionMap, vTexcoord).xyz;
  vec3 vNormal   = normalize(texture(sNormalMap, vTexcoord).xyz);
  vec3 vColor    = texture(sColorMap, vTexcoord).rgb;
  
  f_vColor = vec4(vColor, 1.0) * computeDirectLight(oDirectLights[0], vNormal, vPosition);
}
