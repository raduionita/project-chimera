#version 420 core

#define OGL_TEXTURE_GENERIC   0
#define OGL_ATTACHEMENT_COLOR 0

layout (binding = OGL_TEXTURE_GENERIC) uniform sampler2D sColorMap;

layout (location = OGL_ATTACHEMENT_COLOR) out vec3 vOutput;

const float fOffsets[4] = float[](-1.5, -0.5, 0.5, 1.5);

void main(void) {
  vec3 vResult = vec3(0.0);
  vec2 vTexsize  = textureSize(sColorMap, 0);
  vec2 vTexcoord = gl_FragCoord.xy / vTexsize;
  vec2 vTemp;
  
  for(uint i = 0; i < 4; ++i) {
    for(uint j = 0; j < 4; ++j) {
      vTemp.x  = vTexcoord.x + fOffsets[j] / vTexsize.x;
      vTemp.y  = vTexcoord.y + fOffsets[i] / vTexsize.y;
      vResult += texture(sColorMap, vTemp).rgb;
    }
  }
  
  vOutput = vResult / 16.0;
  //vOutput = texture(sColorMap, vTexcoord).rgb;
}
