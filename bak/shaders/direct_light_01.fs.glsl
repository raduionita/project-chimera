#version 420 core

in vec2 v_vTexcoord;
in vec3 v_vNormal;
in vec3 v_vPosition;

layout (location = 0) out vec4 f_vColor;

layout (binding = 0) uniform sampler2D u_sTexture;

struct DirectionalLight {
  vec3  vColor;
  vec3  vDirection;
  float fAmbientIntensity;
  float fDiffuseIntensity;
};

uniform bool             u_bWireframe = false;
uniform DirectionalLight u_oDirectLight;
uniform vec3  u_vEyePos;
uniform float u_fSpecularIntensity;
uniform float u_fSpecularPower;

void main(void) {
  if(u_bWireframe) {
    f_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  } else {
    float ambient = u_oDirectLight.fAmbientIntensity;
    float diffuse = max(0.0, dot(normalize(v_vNormal), -u_oDirectLight.vDirection));
    float specular = 0.0;
    
    diffuse  = u_oDirectLight.fDiffuseIntensity * diffuse; 
    vec3 vV  = normalize(u_vEyePos - v_vPosition);
    vec3 vR  = normalize(reflect(u_oDirectLight.vDirection, v_vNormal));
    specular = pow(max(0.0, dot(vV, vR)), u_fSpecularPower) * u_fSpecularIntensity;
    
    f_vColor = texture(u_sTexture, v_vTexcoord) * vec4(u_oDirectLight.vColor, 1.0) * (ambient + diffuse + specular);
  }
}
