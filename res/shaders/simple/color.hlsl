@shader GL_VERTEX_SHADER
#version 420 core
// input layout
layout (location = 0) in vec4 a_vPosition;
// entry point
void main() {
  gl_Position = a_vPosition;
}

@shader GL_FRAGMENT_SHADER
#version 420 core
// @todo: implement include...
@include "feature.csl"

@if ()

@else

@endif

#define OGL_TEXTURE_0 0
#define OGL_COLOR_0 0

layout (location = 0) out vec4 f_vColor;

uniform vec4      u_vColor;

void main() {
  f_vColor = u_vColor;
}
