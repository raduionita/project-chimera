#version 420 core

in vs_out_t {
  vec3 vN;
  vec3 vV;
  vec2 vTexcoord;
  vec4 vLightSpacePos;
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

uniform DirectLight u_oDirectLight;
uniform PointLight  u_oPointLights[2];
uniform SpotLight   u_oSpotLights[2];
uniform bool u_bWireframe = false;

layout (binding = 0) uniform sampler2D u_sTexture;
layout (binding = 1) uniform sampler2D u_sShadowMap;

uniform float u_fSpecularPower;
uniform float u_fSpecularIntensity;
uniform vec3  u_fEyePosition;

////////////////////////////////////////////////////////////

layout (location = 0) out vec4 f_vColor;

////////////////////////////////////////////////////////////

float computeShadowFactor(vec4 vLightSpacePos) {
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
  vec3 vV = normalize(u_fEyePosition - fs_in.vV);
  vec3 vR = normalize(reflect(-vDirection, vN));
  float specular = diffuse < 0.0 ? 0.0 : pow(dot(vV, vR), u_fSpecularPower) * u_fSpecularIntensity;
  return vec4(vColor, 1.0) * (ambient + fShadowFactor * (diffuse + specular));
}

vec4 computeDirectLight(DirectLight light, vec3 vN) {
  return computeLight(vN, light.vColor, light.vDirection, light.fAmbientIntensity, light.fDiffuseIntensity, 1.0);
}

vec4 computePointLight(PointLight light, vec3 vN, vec4 vLightSpacePos) {
  vec3 vL = fs_in.vV - light.vPosition;
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
  vec3 vL = fs_in.vV - light.vPosition; // pixel to light vector
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
  if(u_bWireframe) {
    f_vColor = vec4(0.7, 0.7, 0.7, 1.0);
  } else {
    vec3 vN = normalize(fs_in.vN);
    //vec3 vL = normalize(fs_in.vL);
    //vec3 vV = normalize(fs_in.vV);
    
    vec4 vTotalLight;
      vTotalLight += computeDirectLight(u_oDirectLight, vN);
    for(int i = 0; i < 2; i++)
      computePointLight(u_oPointLights[i], vN, fs_in.vLightSpacePos);
    for(int i = 0; i < 2; i++)
      computeSpotLight(u_oSpotLights[i], vN, fs_in.vLightSpacePos);
    
    f_vColor = texture(u_sTexture, fs_in.vTexcoord) * vTotalLight;
    //f_vColor = texture(u_sTexture, fs_in.vTexcoord);
    //f_vColor = vec4((vN + vec3(1.0)) * vec3(0.5), 1.0);
    //f_vColor = texture(u_sTexture, fs_in.vTexcoord) * vec4(u_oDirectLight.vColor, 1.0) * (ambient + diffuse);
  }
}
