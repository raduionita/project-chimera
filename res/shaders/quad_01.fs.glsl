#version 330 core

in vec2 v_vTexcoord;

uniform sampler2D u_sTextureMap;
uniform float u_fNear = 0.1;
uniform float u_fFar  = 1000.0;


layout (location = 0) out vec4 f_vColor;

void main(void) {
  f_vColor = texture(u_sTextureMap, v_vTexcoord);
  
//  float fDepth = texture(u_sTextureMap, v_vTexcoord).x;
//  // linearize depth
//  fDepth = (2.0 * u_fNear) / (u_fFar + u_fNear - fDepth * (u_fFar - u_fNear));
//  f_vColor = vec4(fDepth);
}
