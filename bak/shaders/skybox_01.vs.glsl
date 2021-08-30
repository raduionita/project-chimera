#version 420 core

layout (location = 0) in vec4 a_vPosition;

uniform mat4 u_mMVP;

out vec3 v_vTexcoord;

void main(void) {
  vec4 vP = u_mMVP * a_vPosition;
  v_vTexcoord = a_vPosition.xyz;
  gl_Position = vP.xyww;
}
