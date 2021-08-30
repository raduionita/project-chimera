@shader GL_VERTEX_SHADER
#version 420 core

layout (location = 0) in vec4 a_vPosition;

#define INSTANCE_GRID_XY  0
#define INSTANCE_GRID_XZ  1
#define INSTANCE_GRID_ZY  2
#define INSTANCE_AXIES_X  0
#define INSTANCE_AXIES_Y  1
#define INSTANCE_AXIES_Z  2
#define INSTANCE_ARROWS_X 0
#define INSTANCE_ARROWS_Y 1
#define INSTANCE_ARROWS_Z 2

#define MESH_GRID   0
#define MESH_AXIES  1
#define MESH_ARROWS 2

uniform mat4 u_mPVM;
uniform vec4 u_vColors[3]; // glUniform4fv(id, 3, v)
uniform uint u_iMesh;

out vec4 v_vColor;

// entry point
void main() {
  gl_Position = u_mPVM * a_vPosition;
  v_vColor    = u_vColor;
  
  
  // gl_InstanceID = ?
  // gl_VertedID = ?
}

@shader GL_FRAGMENT_SHADER
#version 420 core

in vec4 v_vColor;

layout (location = 0) out vec4 f_vColor;

void main() {
  f_vColor = v_vColor;
}
