#version 420 core

in vec2 v_vTexcoord;

layout (binding = 0) uniform sampler2D u_sShadowMap;

out vec4 f_vColor;

void main(void) {
  float depth = texture(u_sShadowMap, v_vTexcoord).x;
  depth = 1.0 - (1.0 - depth) * 25.0;
  f_vColor = vec4(depth);
}
