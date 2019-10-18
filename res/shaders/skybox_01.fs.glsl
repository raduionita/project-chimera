#version 420 core

in vec3 v_vTexcoord;

out vec4 f_vColor;

uniform samplerCube u_sSkybox;

void main(void) {
  f_vColor = texture(u_sSkybox, v_vTexcoord);
}
