#shader GL_VERTEX_SHADER
#version 330
// input layout
layout (location = 0) in vec4 a_vPosition;
// entry point
void main() {
  gl_Position = a_vPosition;
}

#shader GL_FRAGMENT_SHADER
#version 330
// @todo: implement include...
#include "feature.glsl"

layout (location = 0) out vec4 f_vColor;

uniform vec4 u_vColor;

void main() {
  f_vColor = u_vColor;
}