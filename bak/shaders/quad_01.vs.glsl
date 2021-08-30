#version 330 core

layout (location = 0) in vec4 a_vPosition;
layout (location = 1) in vec2 a_vTexcoord;

out vec2 v_vTexcoord;

void main(void) {
  gl_Position = a_vPosition;
  v_vTexcoord = a_vTexcoord;

//  const vec4 vertices[4] = vec4[4](
//    vec4(-1.0, -1.0, 0.0, 1.0),
//    vec4( 1.0, -1.0, 0.0, 1.0),
//    vec4(-1.0,  1.0, 0.0, 1.0),
//    vec4( 1.0,  1.0, 0.0, 1.0));
//  gl_Position = vertices[gl_VertexID];
//  
//  const vec2 texcoords[4] = vec2[4](
//    vec2(0.0, 0.0),
//    vec2(1.0, 0.0),
//    vec2(0.0, 1.0),
//    vec2(1.0, 1.0));
//  v_vTexcoord = texcoords[gl_VertexID];
}
