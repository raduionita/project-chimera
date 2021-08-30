#version 420 core

layout (triangles, equal_spacing, ccw) in;

uniform mat4 u_mP;
uniform mat4 u_mV;

layout (binding = 4) uniform sampler2D u_sHeightTex;
uniform float                          u_fHeightFactor;

struct cs_patch_t {
  vec3 vB030;
  vec3 vB021;
  vec3 vB012;
  vec3 vB003;
  vec3 vB102;
  vec3 vB201;
  vec3 vB300;
  vec3 vB210;
  vec3 vB120;
  vec3 vB111;
  vec2 vTexcoord[3];
  vec3 vNormal[3];
  vec3 vTangent[3];
};

in patch cs_patch_t es_patch;

out es_out_t {
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
  es_out.vTexcoord = interpolate2D(es_patch.vTexcoord[0], es_patch.vTexcoord[1], es_patch.vTexcoord[2]);
  es_out.vNormal   = interpolate3D(es_patch.vNormal[0],   es_patch.vNormal[1],   es_patch.vNormal[2]);
  es_out.vTangent  = interpolate3D(es_patch.vTangent[0],  es_patch.vTangent[1],  es_patch.vTangent[2]);
  
  float u = gl_TessCoord.x;
  float v = gl_TessCoord.y;
  float w = gl_TessCoord.z;
  
  float u3 = pow(u, 3);
  float v3 = pow(v, 3);
  float w3 = pow(w, 3);
  float u2 = pow(u, 2);
  float v2 = pow(v, 2);
  float w2 = pow(w, 2);
  
//  es_out.vPosition = interpolate3D(es_patch.vB300, es_patch.vB030, es_patch.vB003);
  es_out.vPosition = es_patch.vB300 * w3 + es_patch.vB030 * u3 + es_patch.vB003 * v3 +
                     es_patch.vB210 * 3.0 * w2 * u + es_patch.vB120 * 3.0 * w * u2 + es_patch.vB201 * 3.0 * w2 * v +
                     es_patch.vB021 * 3.0 * u2 * v + es_patch.vB102 * 3.0 * w * v2 + es_patch.vB012 * 3.0 * u * v2 +
                     es_patch.vB111 * 6.0 * w * v * u;
  
  // displace the vertex along the normal
  //float height = texture(u_sHeightTex, es_out.vTexcoord.xy).x;
  //es_out.vPosition += es_out.vNormal * height * u_fHeightFactor;
  gl_Position = u_mP * u_mV * vec4(es_out.vPosition, 1.0);
}
