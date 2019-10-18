#version 420 core

layout (location = 0) out vec4 f_vColor;

layout (binding = 0) uniform sampler2D u_sDiffuseMap;

uniform bool u_bWireframe = false;

in vec3 v_vPosition_MS;
in vec2 v_vTexcoord;
in vec3 v_vNormal;
in vec3 v_vTangent;

void main(void) {
  if(u_bWireframe)
    f_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  else  
    f_vColor = texture(u_sDiffuseMap, v_vTexcoord);
}
