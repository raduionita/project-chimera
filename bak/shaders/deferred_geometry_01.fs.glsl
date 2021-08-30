#version 420 core

in vs_out_t {
  vec3 vPosition_MS;
  vec2 vTexcoord;
  vec3 vNormal;
  vec3 vTangent;
} fs_in;

layout (location = 0) out vec3 o_vPosition;
layout (location = 1) out vec3 o_vTexcoord;
layout (location = 2) out vec3 o_vNormal;
layout (location = 3) out vec3 o_vTangent;
layout (location = 4) out vec3 o_vDiffuse;

layout (binding = 0) uniform sampler2D u_sDiffuseMap;

void main(void) {
  o_vPosition = fs_in.vPosition_MS;
  o_vTexcoord = vec3(fs_in.vTexcoord, 1.0);
  o_vNormal   = normalize(fs_in.vNormal);
  o_vTangent  = normalize(fs_in.vTangent); 
  o_vDiffuse  = texture(u_sDiffuseMap, fs_in.vTexcoord).rgb;
}
