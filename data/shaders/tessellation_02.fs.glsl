#version 420 core

in es_out_t {
  vec3 vPosition;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
} fs_in;

////////////////////////////////////////////////////////////

struct DirectLight {
  vec3  vColor;
  vec3  vDirection;
  float fAmbientIntensity;
  float fDiffuseIntensity;
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
};

#define USE_DIFFUSE_MAP 0x0001
#define USE_SHADOW_MAP  0x0002
#define USE_NORMAL_MAP  0x0004

#define PICK_MODE_OBJECT    1
#define PICK_MODE_DRAW      2
#define PICK_MODE_PRIMITIVE 3

////////////////////////////////////////////////////////////

uniform DirectLight u_oDirectLight;
uniform PointLight  u_oPointLights[2];
uniform SpotLight   u_oSpotLights[2];

layout (binding = 0) uniform sampler2D u_sDiffuseMap;
layout (binding = 1) uniform sampler2D u_sShadowMap;
layout (binding = 2) uniform sampler2D u_sNormalMap;
layout (binding = 4) uniform sampler2D u_sHeightMap;

uniform float u_fSpecularPower;
uniform float u_fSpecularIntensity;
uniform vec3  u_vEyePosition;

uniform bool u_bWireframe = false;
uniform uint u_nOptions   = 0x0007;

uniform ivec3 u_vPickPixel  = ivec3(-1);
uniform ivec3 u_vIdentifier = ivec3(-1);
uniform int   u_nPickMode   = 1;

////////////////////////////////////////////////////////////

layout (location = 0) out vec4 f_vColor;

////////////////////////////////////////////////////////////

bool hasOption(uint option) {
  return (bool(u_nOptions & option));
}

vec3 computeNormal() {
  if(fs_in.vTangent == vec3(0.0))
    return normalize(fs_in.vNormal);

  vec3 vNormal   = normalize(fs_in.vNormal);
  vec3 vTangent  = normalize(fs_in.vTangent);
  vTangent = normalize(vTangent - dot(vTangent, vNormal) * vNormal); // orthogonalize
  vec3 vBinormal = cross(vTangent, vNormal);
  vec3 vBump = 2.0 * texture(u_sNormalMap, fs_in.vTexcoord).xyz - vec3(1.0);
  mat3 mTBN = mat3(vTangent, vBinormal, vNormal);
  return normalize(mTBN * vBump);
  //return normalize(fs_in.vNormal);
}

float computeShadowFactor(vec4 vLightSpacePos) {
  return 1.0;
  //return textureProj(u_sShadowMap, vLightSpacePos);
  vec3 fProjCoords = vLightSpacePos.xyz / vLightSpacePos.w;
  vec2 vTexcoords;
  vTexcoords.x = 0.5 * fProjCoords.x + 0.5;
  vTexcoords.y = 0.5 * fProjCoords.y + 0.5;
  float z = 0.5 * fProjCoords.z + 0.5;
  float depth = texture(u_sShadowMap, vTexcoords).x;
  if(depth < (z + 0.00001))
    return 0.5;
  else
    return 1.0;  
}

vec4 computeLight(vec3 vN, vec3 vColor, vec3 vDirection, float fAmbientIntensity, float fDiffuseIntensity, float fShadowFactor) {
  float ambient  = fAmbientIntensity;
  float diffuse  = max(0.0, dot(vN, -vDirection)) * fDiffuseIntensity;
  vec3 vV = normalize(u_vEyePosition - fs_in.vPosition);
  vec3 vR = normalize(reflect(-vDirection, vN));
  float specular = diffuse < 0.0 ? 0.0 : pow(dot(vV, vR), u_fSpecularPower) * u_fSpecularIntensity;
  return vec4(vColor, 1.0) * (ambient + fShadowFactor * (diffuse + specular));
}

vec4 computeDirectLight(DirectLight light, vec3 vN) {
  return computeLight(vN, light.vColor, light.vDirection, light.fAmbientIntensity, light.fDiffuseIntensity, 1.0);
}

vec4 computePointLight(PointLight light, vec3 vN, vec4 vLightSpacePos) {
  vec3 vL = fs_in.vPosition - light.vPosition;
  float d = length(vL);
  vL = normalize(vL);
  float fShadowFactor = computeShadowFactor(vLightSpacePos);
  vec4 color = computeLight(vN, light.vColor, vL, light.fAmbientIntensity, light.fDiffuseIntensity, fShadowFactor);
  float attenuation = light.fK0 + light.fK1 * d + light.fK2 * d * d;
  if(attenuation <= 0.0)
    return vec4(0.0);
  else
    return color / attenuation;
};

vec4 computeSpotLight(SpotLight light, vec3 vN, vec4 vLightSpacePos) {
  vec3 vL = fs_in.vPosition - light.vPosition; // pixel to light vector
  float fFactor = dot(normalize(vL), normalize(light.vDirection)); // size of the angle between spot direction & light-pixel
  if(fFactor > light.fCutoff) {
    float d = length(vL);
    vL = normalize(vL);
    float fShadowFactor = computeShadowFactor(vLightSpacePos);
    vec4 color = computeLight(vN, light.vColor, vL, light.fAmbientIntensity, light.fDiffuseIntensity, fShadowFactor);
    float attenuation = light.fK0 + light.fK1 * d + light.fK2 * d * d;
    color /= attenuation;
    //return color * pow(fFactor, light.fCutoff);
    return color * (1.0 - (1.0 - fFactor) / (1.0 - light.fCutoff)); // falloff
  } else {
    return vec4(0.0);
  }
}

void main(void) {
  ivec3 vIdentifier = ivec3(u_vIdentifier.x, u_vIdentifier.y, gl_PrimitiveID+1);

  if(u_bWireframe) {
    f_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  } else if(u_vPickPixel != ivec3(-1) && (u_nPickMode == PICK_MODE_OBJECT) && (u_vPickPixel.x == vIdentifier.x)) {
    f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord) * vec4(1.0, 0.5, 0.5, 1.0);
  } else if(u_vPickPixel != ivec3(-1) && (u_nPickMode == PICK_MODE_DRAW) && (u_vPickPixel.x == vIdentifier.x) && (u_vPickPixel.y == vIdentifier.y)) {
    f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord) * vec4(1.0, 0.5, 0.5, 1.0);
  } else if(u_vPickPixel != ivec3(-1) && (u_nPickMode == PICK_MODE_PRIMITIVE) && (u_vPickPixel.x == vIdentifier.x) && (u_vPickPixel.y == vIdentifier.y) && (u_vPickPixel.z == vIdentifier.z)) {
    f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord) * vec4(1.0, 0.5, 0.5, 1.0);
  } else {
    //vec3 vN = computeNormal();
    vec3 vN = normalize(fs_in.vNormal);
    //vec3 vL = normalize(fs_in.vL);
    //vec3 vV = normalize(fs_in.vPosition);
    
    vec4 vTotalLight;
      vTotalLight += computeDirectLight(u_oDirectLight, vN);
    for(int i = 0; i < 2; i++)
      computePointLight(u_oPointLights[i], vN, vec4(0.0)); // fs_in.vLightSpacePos);
    for(int i = 0; i < 2; i++)
      computeSpotLight(u_oSpotLights[i], vN, vec4(0.0));   // fs_in.vLightSpacePos);
    
    //f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord) * vTotalLight;
    //f_vColor = vec4(0.7, 0.6, 0.5, 1.0);
    //f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord);
    //f_vColor = vec4((vN + vec3(1.0)) * vec3(0.5), 1.0);
    f_vColor = vec4(fs_in.vTexcoord, 0.0, 1.0);
    //f_vColor = texture(u_sDiffuseMap, fs_in.vTexcoord) * vec4(u_oDirectLight.vColor, 1.0) * (ambient + diffuse);
  }
}
