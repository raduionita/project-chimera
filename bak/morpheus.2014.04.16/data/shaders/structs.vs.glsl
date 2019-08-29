#version 430 core
layout(location = 0) in vec3 a_vPosition;
layout(location = 1) in vec4 a_vColor;

out vec4 f_vColor;

void main()
{
  gl_Position = vec4(a_vPosition, 1.0f);
  f_vColor = a_vColor;
}
