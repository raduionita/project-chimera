#version 420 core

layout (location = 0) in vec3 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;
layout (location = 2) in vec3 a_vNormal;

uniform float u_fTime = 0.1;
uniform mat4  u_mM;
uniform mat4  u_mV;

const float PI = 3.14159265358979;

out vs_out_t {
  vec3 vPosition;
  vec4 vColor;
} vs_out;

void main() {
  //float fScale = (sin(u_fTime * PI) + 1.0) * 0.5; // [-1,1] + 1 = [0,2] / 2 = [0,1]
  //gl_Position = vec4(fScale * a_vPosition.x, fScale * a_vPosition.y, a_vPosition.z, 1.0);
  //v_vColor = vec4(clamp(a_vPosition, 0.0, 1.0), 1.0);
  vs_out.vPosition = (u_mM * vec4(a_vPosition, 1.0)).xyz;
  vs_out.vColor    = vec4(1.0, 1.0, 1.0, 1.0);
  gl_Position      = u_mV * u_mM * vec4(a_vPosition, 1.0);
}
