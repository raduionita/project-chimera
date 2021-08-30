#version 420 core

#extension GL_EXT_gpu_shader4 : enable

out ivec3 f_vOutput;

uniform ivec3 u_vIdentifier = ivec3(0);

void main(void) {
  //u_vIdentifier.x = u_nObjectIndex;
  //u_vIdentifier.y = u_nDrawIndex;
  f_vOutput = ivec3(u_vIdentifier.x, u_vIdentifier.y, gl_PrimitiveID+1);
}
