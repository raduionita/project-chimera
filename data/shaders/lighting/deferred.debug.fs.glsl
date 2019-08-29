#version 420 core

// @see ogl.hpp
#define OGL_TEXTURE_GENERIC      0
#define OGL_TEXTURE_DIFFUSE      1
#define OGL_TEXTURE_NORMALS      2
#define OGL_TEXTURE_SPECULAR     3
#define OGL_TEXTURE_POSITIONS    3
#define OGL_TEXTURE_DIRECTSHADOW 4
#define OGL_TEXTURE_SPOTSHADOW   5
#define OGL_TEXTURE_POINTSHADOW  6
#define OGL_TEXTURE_ENVIRONMENT  7

layout (binding = OGL_TEXTURE_GENERIC) uniform sampler2D sGenericMap;

layout (location = 0) out vec4 f_vColor;

void main(void) {
  vec2 vTexcoord = gl_FragCoord.xy / textureSize(sGenericMap, 0);
  f_vColor = texture(sGenericMap, vTexcoord);
  //f_vColor = vec4(vTexcoord.x, vTexcoord.y, 0.0, 1.0);
}
