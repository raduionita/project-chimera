#version 420 core

in vec2 v_vTexcoord;

layout (location = 0) out vec4 f_vColor;

layout (binding = 0) uniform sampler2D u_sTexture;

uniform bool u_bWireframe = false;

void main(void) {
  if(u_bWireframe)
    f_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  else  
    f_vColor = texture(u_sTexture, v_vTexcoord);
}
