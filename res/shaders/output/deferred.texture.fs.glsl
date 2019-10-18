#version 420 core

#define OGL_TEXTURE_GENERIC   0
#define OGL_ATTACHEMENT_COLOR 0

#define OGL_RED   0
#define OGL_GREEN 1
#define OGL_BLUE  2
#define OGL_ALPHA 3

layout (binding = OGL_TEXTURE_GENERIC) uniform sampler2D sTextureMap;

layout (location = OGL_ATTACHEMENT_COLOR) out vec4 vOutput;

uniform float u_fNear =   0.1;
uniform float u_fFar  = 100.0;

void main(void) {
  vec2 vTexcoord = gl_FragCoord.xy / textureSize(sTextureMap, 0);
  vOutput = vec4(texture(sTextureMap, vTexcoord).rgb, 1.0);
  //vOutput = vec4(1.0);
}
