#version 330 core

layout (location = 0) in vec3 a_vPosition;

uniform mat4 u_mMVP;
uniform vec3 u_vColor = vec3(0.6, 0.6, 0.6);

out vec3 v_vColor;

void main() {
  v_vColor = u_vColor;
  gl_Position = u_mMVP * vec4(a_vPosition, 1.0);
}
