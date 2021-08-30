#version 420 core

#define EPSILON 0.00001

#define OGL_ATTACHEMENT_COLOR 0

#define OGL_TEXTURE_NORMALS   2
#define OGL_TEXTURE_NOISE2D   9
#define OGL_TEXTURE_DEPTH     10

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

struct Camera {
  mat4 mV;
  mat4 mP;
}; // oCamera;

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
  
layout (binding = OGL_TEXTURE_DEPTH)     uniform sampler2D u_sDepthMap;
layout (binding = OGL_TEXTURE_NORMALS)   uniform sampler2D u_sNormalsMap;
layout (binding = OGL_TEXTURE_NOISE2D)   uniform sampler2D u_sNoise2dMap;

const int KERNEL_SIZE = 64;

uniform float u_fRadius = 0.03;
uniform mat4  u_mV = mat4(1.0);
uniform mat4  u_mP;
uniform vec3  u_vKernel[KERNEL_SIZE]; // random offsets

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

layout (location = OGL_ATTACHEMENT_COLOR) out float f_fColor;

/**
 * @return vec2
 */
vec2 computeTexcoord() {
  return gl_FragCoord.xy / textureSize(u_sDepthMap, 0);
}

/**
 * Compute position using depth buffer - in View/Camera Space
 * @param  vec2 Texture coordonates used to sample from Depth Map
 * @return vec3 Position in View Space
 */
vec3 computePosition(in vec2 vTexcoord) {
  vec4 cs;
  cs.xy = vTexcoord * 2.0 - 1.0;
  cs.z  = texture(u_sDepthMap, vTexcoord).r * 2.0 - 1.0;
  cs.w  = 1.0;
  vec4 hs = inverse(u_mP * u_mV) * cs;
  return (u_mV * vec4(hs.xyz / hs.w, 1.0)).xyz;
}

/**
 * Get fragment's normal vector
 * @param  vec2 Normal map texture coordonate
 * @return vec3 Fragment normal
 */
vec3 computeNormal(in vec2 vTexcoord) {
  return (u_mV * vec4(normalize((vec4(texture(u_sNormalsMap, vTexcoord).xyz, 0.0)).xyz), 0.0)).xyz;
}

void main(void) {
  vec2 vTexcoord   = computeTexcoord();
  vec3 vPosition   = computePosition(vTexcoord);
  vec3 vNormal     = computeNormal(vTexcoord);
  vec3 vRandom     = texture(u_sNoise2dMap, gl_FragCoord.xy / textureSize(u_sNoise2dMap, 0)).xyz; 
  
  vec3 vTangent    = normalize(vRandom - vNormal * dot(vRandom, vNormal));
  vec3 vBinormal   = cross(vNormal, vTangent);
  mat3 mTBN        = mat3(vTangent, vBinormal, vNormal);
  
  float fOcclusion = 0.0;
  
  for(int i = 0; i < KERNEL_SIZE; ++i) {
    vec3 vSamplePosition = vPosition + mTBN * u_vKernel[i] * u_fRadius;
    
    vec4 vOffsetPosition = vec4(vSamplePosition, 1.0);
    
    vOffsetPosition     = u_mP * vOffsetPosition;               // clip space
    vOffsetPosition.xy /= vOffsetPosition.w;                    // [-1, 1] // NDC space
    vOffsetPosition.xy  = vOffsetPosition.xy * 0.5 + vec2(0.5); // [ 0, 1] // [-1, 1] / 2 = [-0.5, 0.5] + 0.5 = [0, 1] // texture space
    
    float fSampleDepth = computePosition(vOffsetPosition.xy).z;
    
    float fRangeCheck  = smoothstep(0.0, 1.0, u_fRadius / abs(vPosition.z - fSampleDepth));
    
    fOcclusion += (fSampleDepth >= vSamplePosition.z ? 1.0 : 0.0) * fRangeCheck;
  }
  
  fOcclusion = 1.0 - fOcclusion / KERNEL_SIZE;
  
  f_fColor = pow(fOcclusion, 3.0);
  //f_fColor = fOcclusion;
}
