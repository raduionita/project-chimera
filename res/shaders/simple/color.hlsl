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

layout (binding = OGL_TEXTURE_0) uniform sampler2D u_sTexture;
                                 uniform vec4      u_vColor;

void main() {
  vec2 vTexcoord = gl_FragCoord.xy / textureSize(u_sTexture, 0);
  f_vColor = vec4(texture(u_sTexture, vTexcoord).rgb, 1.0); // , u_vColor;
}
