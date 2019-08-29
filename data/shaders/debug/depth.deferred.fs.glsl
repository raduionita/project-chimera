#version 420 core

#define OGL_TEXTURE_GENERIC   0
#define OGL_ATTACHEMENT_COLOR 0

layout (binding = OGL_TEXTURE_GENERIC) uniform sampler2D sDepthMap;

layout (location = OGL_ATTACHEMENT_COLOR) out vec4 vOutput;

uniform float u_fNear =   0.1;
uniform float u_fFar  = 100.0;

void main(void) {
  vec2 vTexcoord = gl_FragCoord.xy / textureSize(sDepthMap, 0);
  float fDepth = texture(sDepthMap, vTexcoord).r; // [ 0, 1]
  vOutput = vec4(vec3(pow(fDepth, 20.0)), 1.0);
  fDepth = 2.0 * fDepth - 1.0;                    // [-1, 1]
  fDepth = 2.0 * (u_fNear * u_fFar) / (u_fFar + u_fNear - fDepth * (u_fFar - u_fNear));
  //vOutput = vec4(1.0);
}
