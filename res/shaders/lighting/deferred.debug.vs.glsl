#version 420 core

const vec4 vertices[4] = vec4[4](
  vec4(-1.0, -1.0, 0.0, 1.0),
  vec4( 1.0, -1.0, 0.0, 1.0),
  vec4(-1.0,  1.0, 0.0, 1.0),
  vec4( 1.0,  1.0, 0.0, 1.0)
);

void main(void) {
  gl_Position = vertices[gl_VertexID];
}
