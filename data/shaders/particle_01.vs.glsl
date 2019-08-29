#version 420 core

layout (location = 0) in float a_fType;
layout (location = 1) in vec3  a_vPosition;
layout (location = 2) in vec3  a_vVelocity;
layout (location = 3) in float a_fAge;

out vs_out_t {
  float fType;
  vec3  vPosition;
  vec3  vVelocity;
  float fAge;
} vs_out;

void main(void) {
  vs_out.fType     = a_fType;
  vs_out.vPosition = a_vPosition;
  vs_out.vVelocity = a_vVelocity;
  vs_out.fAge      = a_fAge;
}
