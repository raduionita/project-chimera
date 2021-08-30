#version 420 core

in vec2 v_vTexcoord;

layout (binding = 0) uniform sampler2D u_sColorMap;
layout (binding = 1) uniform sampler2D u_sMotionMap;

layout (location = 0) out vec4 f_vColor;

void main(void) {
  vec2 vMotion = texture(u_sMotionMap, v_vTexcoord).xy / 2.0;
  
  vec4 vColor = vec4(0.0);
  
  vec2 vTexcoord = v_vTexcoord;
  
  vColor += texture(u_sColorMap, vTexcoord) * 0.4;
  vTexcoord -= vMotion;
  vColor += texture(u_sColorMap, vTexcoord) * 0.3;
  vTexcoord -= vMotion;
  vColor += texture(u_sColorMap, vTexcoord) * 0.2;
  vTexcoord -= vMotion;
  vColor += texture(u_sColorMap, vTexcoord) * 0.1;
  
  //vColor = texture(u_sColorMap, v_vTexcoord);
  
  f_vColor = vColor;
}
