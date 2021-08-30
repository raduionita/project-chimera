#version 420 core

in vs_out_t {
  vec3 vPosition;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
  //flat ivec3 vIdentifier;
} fs_in;

////////////////////////////////////////////////////////////

struct DirectLight {
  bool  bEnabled;
  vec3  vColor;
  vec3  vDirection;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  int   iShadowIndex;
  mat4  mVP;
};

struct PointLight {
  bool  bEnabled;
  vec3  vColor;
  vec3  vPosition;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  float fK0;
  float fK1;
  float fK2;
  int   iShadowIndex;
};

struct SpotLight {
  bool  bEnabled;
  vec3  vColor;
  vec3  vPosition;
  vec3  vDirection;
  float fCutoff;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  float fK0;
  float fK1;
  float fK2;
  int   iShadowIndex;
  mat4  mVP;
};

struct Camera {
  vec3 vPosition;
};

struct Scene {
  int iNumDirectLights;
  int iNumPointLights;
  int iNumSpotLights;
};

struct Material {
  uint  nMaps; // HAS_DIFFUSE HAS_NORMALS HAS_SPECULAR HAS_ENVIRONMENT
  
  vec3  vDiffuseColor;
  float fDiffuseIntensity;
  vec3  vSpecularColor;
  float fSpecularPower;
  float fSpecularIntensity;
};

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
#define OGL_TEXTURE_DIRECTSHADOW 4
#define OGL_TEXTURE_SPOTSHADOW   5
#define OGL_TEXTURE_POINTSHADOW  6
#define OGL_TEXTURE_ENVIRONMENT  7

////////////////////////////////////////////////////////////

uniform DirectLight u_oDirectLight;
uniform SpotLight   u_oSpotLight;
uniform PointLight  u_oPointLight;
uniform Camera      u_oCamera;
uniform Scene       u_oScene;

layout (binding = OGL_TEXTURE_DIFFUSE)      uniform sampler2D       u_sDiffuseMap;
layout (binding = OGL_TEXTURE_NORMALS)      uniform sampler2D       u_sNormalMap;
layout (binding = OGL_TEXTURE_SPECULAR)     uniform sampler2D       u_sSpecularMap;
layout (binding = OGL_TEXTURE_ENVIRONMENT)  uniform samplerCube     u_sEnvironmentMap;

layout (binding = OGL_TEXTURE_DIRECTSHADOW) uniform sampler2DShadow u_sDirectShadowMap;
layout (binding = OGL_TEXTURE_SPOTSHADOW)   uniform sampler2DShadow u_sSpotShadowMap;
layout (binding = OGL_TEXTURE_POINTSHADOW)  uniform samplerCube     u_sPointShadowMap;

uniform vec3  u_vDiffuseColor;
uniform float u_fDiffuseIntensity = 1.0; // [0, 1] = [none, full]
uniform vec3  u_vSpecularColor;
uniform float u_fSpecularPower;          // shininess
uniform float u_fSpecularIntensity;      // [0, 1]
uniform float u_fPcfSize = 1.0;          // default: 1.0 // 
uniform float u_fPcfStep = 1.0;          // default: 1.0 // @see computeShadowFactor

////////////////////////////////////////////////////////////

layout (location = 0) out vec4 f_vColor;

////////////////////////////////////////////////////////////

/**
 * Gamma correction
 * @param  vec3 vColor
 * @return vec3
 */
vec3 computeGamma(vec3 vColor) {
  return pow(vColor, vec3(2.2)); // or 1.0 / 2.2
}

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

/**
 * PCF Shadow Map Sampling
 * @param  vec4  vPositionLS position if fragment in light space
 * @return float fFactor     [0, 1]
 * @todo   Adjust algorithm to support u_fPcfSize & u_fPcfStep fractions
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
    for(float y = -u_fPcfSize; y <= u_fPcfSize; y += u_fPcfStep) { // 1.0
      for(float x = -u_fPcfSize; x <= u_fPcfSize; x += u_fPcfStep) { // 1.0
        fFactor += texture(sShadowMap, vec3(vTexcoords.x + x * vOffset.x, vTexcoords.y + y * vOffset.y, vTexcoords.z + EPSILON));
      }
    }
    
    float fPcfSize2 = (2 * u_fPcfSize + 1.0);
    fPcfSize2 *= fPcfSize2;                   // no specular hightlights inside shadow
    fFactor = fFactor / fPcfSize2;            // this returns hard shadows w/ soft edges
    
    // fFactor = (0.5 + (fFactor / 9.0) * 0.5); // => [0, 1] // this fucks up lighting, the shadow is too bright
  }
  return fFactor;
}

float computeShadowFactor(in samplerCube sShadowMap, in vec3 vL) {
  //return texture(sShadowMap, vL).r;
  
  vec3 vLAbs = abs(vL);
  float fNear = 0.1;
  float fFar  = 1000.0;
  float fDepth = max(vLAbs.x, max(vLAbs.y, vLAbs.z)); // greates margin of light to fragment vector
  fDepth = ((fFar + fNear) / (fFar - fNear)) - ((2.0 * fFar * fNear) / (fFar - fNear)) / fDepth;
  fDepth = (fDepth + 1.0) * 0.5;
  vL.y *= -1.0;                                       // FIX cubemap's inverted Y axis
  float fShadow = texture(sShadowMap, vL).r;
  
  if(fShadow + EPSILON > fDepth)
    return 1.0;
  return 0.0;
}

/**
 * @todo Improve algorithm to support Material colors
 */
vec4 computeDirectLight(DirectLight oLight, vec3 vN) {
  vec3  vL = -normalize(oLight.vDirection);
  float NdotL = max(0.0, dot(vN, vL));
  float ambient = oLight.fAmbientIntensity;
  float diffuse = NdotL * oLight.fDiffuseIntensity;
  vec3  vV = normalize(u_oCamera.vPosition - fs_in.vPosition);
  vec3  vR = normalize(reflect(-vL, vN)); // replace by vH
  float VdotR = dot(vV, vR);
  float specular = NdotL <= 0.0 ? 0.0 : max(0.0, pow(VdotR, u_fSpecularPower)) * u_fSpecularIntensity;
  float fShadow  = computeShadowFactor(u_sDirectShadowMap, oLight.mVP * vec4(fs_in.vPosition, 1.0));
  vec3  vResult = oLight.vColor * min(ambient + fShadow * (diffuse + specular), 1.0);
  vResult = computeGamma(vResult);
  return vec4(vResult, 1.0);
}

/**
 * @todo Improve algorithm to support Material colors
 */
vec4 computePointLight(PointLight oLight, vec3 vN) {
  vec3  vL = oLight.vPosition - fs_in.vPosition;
  float fDistance = length(vL);
  float fShadow   = computeShadowFactor(u_sPointShadowMap, -vL);
  vL = normalize(vL);
  float NdotL = max(0.0, dot(vN, vL));
  float fAmbient  = /* NdotL * */ oLight.fAmbientIntensity;
  float fDiffuse  = NdotL * oLight.fDiffuseIntensity;
  vec3  vV = normalize(u_oCamera.vPosition - fs_in.vPosition);
  //vec3  vR = normalize(reflect(-vL, vN)); // replace by vH
  vec3  vH = normalize(vV + vL);
  //float VdotR = dot(vV, vR);
  float HdotN = dot(vH, vN);
  float fAttenuation = oLight.fK0 + oLight.fK1 * fDistance + oLight.fK2 * fDistance * fDistance;
  //float fSpecular = NdotL <= 0.0 ? 0.0 : max(0.0, pow(VdotR, u_fSpecularPower)) * u_fSpecularIntensity;
  float fSpecular = NdotL <= 0.0 ? 0.0 : max(0.0, pow(HdotN, u_fSpecularPower)) * u_fSpecularIntensity;
  vec3  vResult   = oLight.vColor * min(fShadow * (fDiffuse + fSpecular), 1.0);
  //vResult += texture(u_sEnvironmentMap, -vL).rgb;
  vResult += oLight.vColor * fAmbient;
  vResult /= fAttenuation;
  //vResult  = computeGamma(vResult);
  return vec4(vResult, 1.0);
};

/**
 * @param SpotLight oLight
 * @param vec3      vN     computed surface normal
 * @todo  Improve algorithm to support Material colors
 */
vec4 computeSpotLight(SpotLight oLight, vec3 vN) {
  vec3 vResult;
  vec3 vL = oLight.vPosition - fs_in.vPosition; // pixel to light vector
  float fDistance = length(vL);
  vL = normalize(vL);
  float fNdotL = max(0.0, dot(vN, vL));
  float fAttenuation = oLight.fK0 + oLight.fK1 * fDistance + oLight.fK2 * fDistance * fDistance;
  float fFactor = dot(-vL, normalize(oLight.vDirection)); // size of the angle between spot direction & light-pixel
  
  float fAmbient = fNdotL * fFactor * oLight.fAmbientIntensity;                                             // ambient coefficient
  
  if(fFactor > oLight.fCutoff) {
    vec3  vV = normalize(u_oCamera.vPosition - fs_in.vPosition);
    vec3  vR = normalize(reflect(-vL, vN)); // replace by vH
    float fDiffuse  = fNdotL * oLight.fDiffuseIntensity;                                                    // diffuse coefficient
    float fVdotR    = dot(vV, vR);
    float fSpecular = fNdotL <= 0.0 ? 0.0 : max(0.0, pow(fVdotR, u_fSpecularPower)) * u_fSpecularIntensity; // specular coefficient
    float fShadow   = computeShadowFactor(u_sSpotShadowMap, oLight.mVP * vec4(fs_in.vPosition, 1.0));
    
    vResult  = oLight.vColor * min(fShadow * (fDiffuse + fSpecular), 1.0);
    vResult  = vResult * (1.0 - (1.0 - fFactor) / (1.0 - oLight.fCutoff)); // falloff
    //vResult = vResult * pow(fFactor, oLight.fExponent);
  } else {
    // vResult = oLight.vColor * fAmbient;
    // vResult /= fAttenuation;
    // vResult = vec4(0.0);
  }
  
  vResult += oLight.vColor * fAmbient;
  vResult /= fAttenuation;
  vResult  = computeGamma(vResult);
  
  return vec4(vResult, 1.0);
}

void main(void) {
  vec3 vN = computeNormal();
  
  vec4 vTotalLight = vec4(0.0, 0.0, 0.0, 1.0);
    
  // for(int i = 0; i < u_oScene.iNumDirectLights && i < MAX_DIRECT_LIGHTS; i++)
  // for(int i = 0; i < u_oScene.iNumPointLights && i < MAX_POINT_LIGHTS; i++)
  // for(int i = 0; i < u_oScene.iNumSpotLights && i < MAX_SPOT_LIGHTS + 1; i++)
  
  vec3 vColor = vec3(0.0, 0.0, 0.0);
  
  if(u_oDirectLight.bEnabled) {
    vTotalLight = computeDirectLight(u_oDirectLight, vN);
    vTotalLight = vec4(0.0, 0.0, 0.0, 1.0);
  }
  if(u_oSpotLight.bEnabled) {
    vTotalLight = computeSpotLight(u_oSpotLight, vN);
    vTotalLight = vec4(0.0, 0.0, 0.0, 1.0);
  }
  if(u_oPointLight.bEnabled) {
    vTotalLight = computePointLight(u_oPointLight, vN);
    //vTotalLight = vec4(0.0, 0.0, 0.0, 1.0);
  }
  
  f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord) * vTotalLight;
  //f_vColor = vec4(1.0);
}
