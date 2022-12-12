#version 420 core

out vec2 v_vTexcoord;

void main(void) {
  const vec4 vertices[4] = vec4[4](
    vec4(-1.0, -1.0, 0.0, 1.0),
    vec4( 1.0, -1.0, 0.0, 1.0),
    vec4(-1.0,  1.0, 0.0, 1.0),
    vec4( 1.0,  1.0, 0.0, 1.0));
  gl_Position = vertices[gl_VertexID];
  
  const vec2 texcoords[4] = vec2[4](
    vec2(0.0, 0.0),
    vec2(1.0, 0.0),
    vec2(0.0, 1.0),
    vec2(1.0, 1.0));
  v_vTexcoord = texcoords[gl_VertexID];
}
