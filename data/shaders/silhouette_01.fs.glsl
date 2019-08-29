#version 330 core

layout (location = 0) out vec4 f_vColor;

in gs_out_t {
  vec4 vColor;
} fs_in;

uniform bool u_bWireframe = false;

void main(void) {
  //f_vColor = vec4(1.0, 0.0, 0.0, 1.0);
  if(u_bWireframe)
    f_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  else  
    f_vColor = fs_in.vColor;
}
