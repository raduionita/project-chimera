#version 330 core

layout (location = 0) in vec3 a_vPosition;

uniform float u_fTime = 0.1;
uniform mat4  u_mMVP;

const float PI = 3.14159265358979;

out vec4 v_vColor;

void main() {
  //float fScale = (sin(u_fTime * PI) + 1.0) * 0.5; // [-1,1] + 1 = [0,2] / 2 = [0,1]
  //gl_Position = vec4(fScale * a_vPosition.x, fScale * a_vPosition.y, a_vPosition.z, 1.0);
  //v_vColor = vec4(clamp(a_vPosition, 0.0, 1.0), 1.0);
  v_vColor = vec4(1.0, 1.0, 1.0, 1.0);
  gl_Position = u_mMVP * vec4(a_vPosition, 1.0);
}
