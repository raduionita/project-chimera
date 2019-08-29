#version 330 core

layout (location = 0) out vec4 f_vColor;

in vec3 v_vColor;

void main(void) {
  f_vColor = vec4(v_vColor, 1.0);
}
