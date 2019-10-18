#version 420 core

layout (vertices = 4) out;

uniform vec3 u_vEyePosition;

in vs_out_t {
  vec3 vPosition; // model space
  vec2 vTexcoord; // model space
  vec3 vNormal;   // model space
  vec3 vTangent;  // model space
} cs_in[];

out cs_out_t {
  vec3 vPosition; // model space
  vec2 vTexcoord; // model space
  vec3 vNormal;   // model space
  vec3 vTangent;  // model space
} cs_out[];

float computeTessLevel(float d0, float d1) {
  float avrg = (d0 + d1) / 2.0;
  
  if(avrg <= 2.0)
    return 10.0;
  else if(avrg <= 5.0)
    return 7.0;
  else if (avrg <= 10.0)
    return 5.0;
  else  
    return 3.0;
}

void main(void) {
  // set control points of the output patch
  cs_out[gl_InvocationID].vPosition = cs_in[gl_InvocationID].vPosition;
  cs_out[gl_InvocationID].vTexcoord = cs_in[gl_InvocationID].vTexcoord;
  cs_out[gl_InvocationID].vNormal   = cs_in[gl_InvocationID].vNormal;
  cs_out[gl_InvocationID].vTangent  = cs_in[gl_InvocationID].vTangent;
  
  // calculate distance from camera to the 3 control points
  float e2v0 = distance(u_vEyePosition, cs_in[0].vPosition); // cp0
  float e2v1 = distance(u_vEyePosition, cs_in[1].vPosition); // cp1
  float e2v2 = distance(u_vEyePosition, cs_in[2].vPosition); // cp2
  
  // calculate tessellation levels
  gl_TessLevelOuter[0] = computeTessLevel(e2v1, e2v2);
  gl_TessLevelOuter[1] = computeTessLevel(e2v2, e2v0);
  gl_TessLevelOuter[2] = computeTessLevel(e2v0, e2v1);
  gl_TessLevelInner[0] = gl_TessLevelOuter[2];
}
