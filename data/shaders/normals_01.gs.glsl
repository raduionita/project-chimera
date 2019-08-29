#version 420 core

layout (points) in;
layout (line_strip) out;
layout (max_vertices = 6) out;

in vs_out_t {
  vec3 vPositionWS;
  vec3 vNormalWS;
  vec3 vTangentWS;
  vec3 vBinormalWS;
} gs_in[];

out gs_out_t {
  vec3 vColor;
} gs_out;

uniform mat4  u_mVP;
uniform float u_fScale = 0.1;

void main(void) {
  gl_Position = u_mVP * vec4(gs_in[0].vPositionWS, 1.0);
  gs_out.vColor = vec3(1.0, 0.0, 0.0);
  EmitVertex();
  gl_Position = u_mVP * vec4(gs_in[0].vPositionWS + normalize(gs_in[0].vNormalWS) * u_fScale, 1.0);
  gs_out.vColor = vec3(1.0, 0.0, 0.0);
  EmitVertex();
  EndPrimitive();
  
//  gl_Position = u_mVP * vec4(gs_in[0].vPositionWS, 1.0);
//  gs_out.vColor = vec3(0.0, 1.0, 0.0);
//  EmitVertex();
//  gl_Position = u_mVP * vec4(gs_in[0].vPositionWS + normalize(gs_in[0].vTangentWS) * u_fScale, 1.0);
//  gs_out.vColor = vec3(0.0, 1.0, 0.0);
//  EmitVertex();
//  EndPrimitive();
//  
//  gl_Position = u_mVP * vec4(gs_in[0].vPositionWS, 1.0);
//  gs_out.vColor = vec3(0.0, 0.0, 1.0);
//  EmitVertex();
//  gl_Position = u_mVP * vec4(gs_in[0].vPositionWS + cross(normalize(gs_in[0].vTangentWS), normalize(gs_in[0].vNormalWS)) * u_fScale, 1.0);
//  gs_out.vColor = vec3(0.0, 0.0, 1.0);
//  EmitVertex();
//  EndPrimitive();
}
