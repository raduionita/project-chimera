#version 420 core

layout (points) in;
layout (triangle_strip) out;
layout (max_vertices = 4) out;

uniform mat4  u_mVP;
uniform vec3  u_vCameraPosition;
uniform float u_fBillboardSize   = 1.0;

out vec2 v_vTexcoord;

void main(void) {
  vec3 vP = gl_in[0].gl_Position.xyz;
  
  vec3 vForward = normalize(u_vCameraPosition - vP);
  vec3 vUp      = vec3(0.0, 1.0, 0.0);
  vec3 vRight   = normalize(cross(vForward, vUp)) * u_fBillboardSize;
  
  vP -= vRight;
  gl_Position = u_mVP * vec4(vP, 1.0);
  v_vTexcoord = vec2(0.0, 0.0);
  EmitVertex();
  
  vP.y += u_fBillboardSize;
  gl_Position = u_mVP * vec4(vP, 1.0);
  v_vTexcoord = vec2(0.0, 1.0);
  EmitVertex();
  
  vP += vRight;
  vP.y -= u_fBillboardSize;
  gl_Position = u_mVP * vec4(vP, 1.0);
  v_vTexcoord = vec2(1.0, 0.0);
  EmitVertex();
  
  vP.y += u_fBillboardSize;
  gl_Position = u_mVP * vec4(vP, 1.0);
  v_vTexcoord = vec2(1.0, 1.0);
  EmitVertex();
  
  EndPrimitive();
}
