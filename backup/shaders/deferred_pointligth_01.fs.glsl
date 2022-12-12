#version 420 core

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

////////////////////////////////////////////////////////////

layout (binding = 0) uniform sampler2D u_sPositionMap;
layout (binding = 2) uniform sampler2D u_sNormalMap;
layout (binding = 4) uniform sampler2D u_sColorMap;

uniform DirectLight u_oDirectLight;
uniform PointLight  u_oPointLight;
uniform SpotLight   u_oSpotLight;

uniform float u_fSpecularPower;
uniform float u_fSpecularIntensity;

uniform vec3  u_vEyePosition;

uniform int u_iLightType;

uniform vec2 u_vScreenSize;

////////////////////////////////////////////////////////////

layout (location = 0) out vec4 f_vColor;

////////////////////////////////////////////////////////////

vec4 computeLight(vec3 vColor, float fAmbientIntensity, float fDiffuseIntensity, vec3 vDirection, vec3 vPosition, vec3 vNormal) {
  float ambient  = fAmbientIntensity;
  float diffuse  = max(0.0, dot(vNormal, -vDirection)) * fDiffuseIntensity;
  vec3 vV = normalize(u_vEyePosition - vPosition);
  vec3 vR = normalize(reflect(-vDirection, vNormal));
  float specular = diffuse < 0.0 ? 0.0 : pow(dot(vV, vR), u_fSpecularPower) * u_fSpecularIntensity;
  return vec4(vColor, 1.0) * (ambient + diffuse + specular);
}

vec4 computeDirectLight(vec3 vPosition, vec3 vNormal) {
  return computeLight(u_oDirectLight.vColor, 
                      u_oDirectLight.fAmbientIntensity,
                      u_oDirectLight.fDiffuseIntensity,
                      u_oDirectLight.vDirection,
                      vPosition,
                      vNormal);
}

vec4 computePointLight(vec3 vPosition, vec3 vNormal) {
  vec3  vDirection = vPosition - u_oPointLight.vPosition;
  float fDistance  = length(vDirection);
  vDirection = normalize(vDirection);
  
  vec4 vColor = computeLight(u_oPointLight.vColor, 
                             u_oPointLight.fAmbientIntensity,
                             u_oPointLight.fDiffuseIntensity,
                             vDirection,
                             vPosition,
                             vNormal);
  
  float fAttenuation = max(1.0, u_oPointLight.fK0 + u_oPointLight.fK1 * fDistance + u_oPointLight.fK2 * fDistance * fDistance);
  
  return vColor / fAttenuation;
}

vec2 computeTexcoord() {
  return gl_FragCoord.xy / u_vScreenSize;
}

////////////////////////////////////////////////////////////

void main(void) {
  vec2 texcoord = computeTexcoord();
  vec3 position = texture(u_sPositionMap, texcoord).xyz;
  vec3 color    = texture(u_sColorMap, texcoord).rgb;
  vec3 normal   = normalize(texture(u_sNormalMap, texcoord).xyz);
  
  f_vColor = vec4(1.0);
  f_vColor = vec4(color, 1.0);
  f_vColor = vec4(color, 1.0) * computePointLight(position, normal);
}
