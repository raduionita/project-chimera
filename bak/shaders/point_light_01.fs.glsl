#version 420 core

in vs_out_t {
  vec3 vN;
  vec3 vL;
  vec3 vV;
  vec2 vTexcoord;
} fs_in;

////////////////////////////////////////////////////////////

struct DirectLight {
  vec3  vColor;
  vec3  vDirection;
  float fAmbientIntensity;
  float fDiffuseIntensity;
};

struct PointLight
{
  vec3  vColor;
  vec3  vPosition;
  float fAmbientIntensity;
  float fDiffuseIntensity;
  float fK0;
  float fK1;
  float fK2;
};

struct SpotLight
{
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
uniform bool u_bWireframe = false;
uniform sampler2D u_sTexture;

uniform float u_fSpecularPower     = 32.0;
uniform float u_fSpecularIntensity = 0.5;
uniform vec3  u_fEyePosition       = vec3(0.0, 0.0, 0.0);

////////////////////////////////////////////////////////////

layout (location = 0) out vec4 f_vColor;

////////////////////////////////////////////////////////////

vec4 computeLight(vec3 vN, vec3 vColor, vec3 vDirection, float fAmbientIntensity, float fDiffuseIntensity) {
  vec4 ambient  = vec4(vColor, 1.0) * fAmbientIntensity;
  vec4 diffuse  = vec4(vColor, 1.0) * max(0.0, dot(vN, vDirection)) * fDiffuseIntensity;
  vec3 vV = normalize(u_fEyePosition - fs_in.vV);
  vec3 vR = normalize(reflect(-vDirection, vN));
  vec4 specular = vec4(vColor, 1.0) * pow(dot(vV, vR), u_fSpecularPower) * u_fSpecularIntensity;
  return ambient + diffuse + specular;
}

vec4 computeDirectLight(vec3 vN) {
  return computeLight(vN, u_oDirectLight.vColor, u_oDirectLight.vDirection, u_oDirectLight.fAmbientIntensity, u_oDirectLight.fDiffuseIntensity);
}

vec4 computePointLight(int i, vec3 vN) {
  vec3 vL = u_oPointLights[i].vPosition - fs_in.vV;
  float d = length(vL);
  vL = normalize(vL);
  vec4 color = computeLight(vN, u_oPointLights[i].vColor, vL, u_oPointLights[i].fAmbientIntensity, u_oPointLights[i].fDiffuseIntensity);
  float attenuation = u_oPointLights[i].fK0 + u_oPointLights[i].fK1 * d + u_oPointLights[i].fK2 * d * d;
  return color / attenuation;
};

void main(void) {
  if(u_bWireframe) {
    f_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  } else {
    vec3 vN = normalize(fs_in.vN);
    //vec3 vL = normalize(fs_in.vL);
    //vec3 vV = normalize(fs_in.vV);
    
    vec4 vTotalLight;
    vTotalLight += computeDirectLight(vN);
    for(int i = 0; i < 2; i++)
      vTotalLight += computePointLight(i, vN);
    
    f_vColor = texture(u_sTexture, fs_in.vTexcoord) * vTotalLight;
    
    //f_vColor = vec4((vN + vec3(1.0)) * vec3(0.5), 1.0);
    //f_vColor = texture(u_sTexture, fs_in.vTexcoord) * vec4(u_oDirectLight.vColor, 1.0) * (ambient + diffuse);
  }
}
