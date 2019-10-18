#version 420 core

uniform sampler2D u_sDiffuseMap;

in vec2 v_vTexcoord;

out vec4 f_vColor;

void main(void) {
  f_vColor = texture(u_sDiffuseMap, v_vTexcoord);
  /*if(f_vColor.r == 0.0 && f_vColor.g == 0.0 && f_vColor.b == 0.0)
    discard;*/
}
