#version 420 core

layout (triangles, equal_spacing, ccw) in;

uniform mat4 u_mP;
uniform mat4 u_mV;

layout (binding = 4) uniform sampler2D u_sHeightTex;
uniform float                          u_fHeightFactor;

in cs_out_t {
  vec3 vPosition; // model space
  vec2 vTexcoord; // model space
  vec3 vNormal;   // model space
  vec3 vTangent;  // model space
} es_in[];

out cs_out_t {
  vec3 vPosition;
  vec2 vTexcoord;
  vec3 vNormal; 
  vec3 vTangent;
} es_out;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2) {
  return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2) {
  return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(void) {
  // interpolate using baricentric coordonates
  es_out.vPosition = interpolate3D(es_in[0].vPosition, es_in[1].vPosition, es_in[2].vPosition);
  es_out.vTexcoord = interpolate2D(es_in[0].vTexcoord, es_in[1].vTexcoord, es_in[2].vTexcoord);
  es_out.vNormal   = interpolate3D(es_in[0].vNormal,   es_in[1].vNormal,   es_in[2].vNormal);
  es_out.vNormal   = normalize(es_out.vNormal);
  es_out.vTangent  = interpolate3D(es_in[0].vTangent,  es_in[1].vTangent,  es_in[2].vTangent);
  es_out.vTangent  = normalize(es_out.vTangent);
  
  // displace the vertex along the normal
  float height = texture(u_sHeightTex, es_out.vTexcoord.xy).x;
  es_out.vPosition += es_out.vNormal * height * u_fHeightFactor;
  gl_Position = u_mP * u_mV * vec4(es_out.vPosition, 1.0);
}
