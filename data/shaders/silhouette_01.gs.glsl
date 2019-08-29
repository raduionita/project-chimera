#version 420 core

struct PointLight {
  vec3  vPosition;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

layout (triangles_adjacency) in;
layout (line_strip, max_vertices = 6) out;

in vs_out_t {
  vec3 vPosition;
  vec4 vColor;
} gs_in[];

out gs_out_t {
  vec3 vPosition;
  vec4 vColor;
} gs_out;

uniform mat4 u_mP;

uniform PointLight u_oPointLight;

const float EPSILON = 0.00001;

void EmitLine(int start, int end) {
  gs_out.vPosition = gs_in[start].vPosition;
  gs_out.vColor    = gs_in[start].vColor;
  gl_Position = u_mP * gl_in[start].gl_Position;
  EmitVertex();
  gs_out.vPosition = gs_in[end].vPosition;
  gs_out.vColor    = gs_in[end].vColor;
  gl_Position = u_mP * gl_in[end].gl_Position;
  EmitVertex();
  EndPrimitive();
}

void main(void) {
  vec3 e1 = gs_in[2].vPosition - gs_in[0].vPosition;      // 1 ----- 2 -e4-- 3 
  vec3 e2 = gs_in[4].vPosition - gs_in[0].vPosition;      //  \     / \     /  
  vec3 e3 = gs_in[1].vPosition - gs_in[0].vPosition;      //  e3   e1  e5  /   
  vec3 e4 = gs_in[3].vPosition - gs_in[2].vPosition;      //    \ /     \ /    
  vec3 e5 = gs_in[4].vPosition - gs_in[2].vPosition;      //     0 -e2-- 4     
  vec3 e6 = gs_in[5].vPosition - gs_in[4].vPosition;      //      \     /      
  //                                                      //       \   e6      
  vec3 vN = cross(e1, e2);                                //        \ /        
  vec3 vL = u_oPointLight.vPosition - gs_in[0].vPosition; //         5         

  if(dot(vN, vL) > EPSILON) { // if (024) face in view of light
    vN = cross(e3, e1);
    if(dot(vN, vL) <= 0.0) { // if adjacent (102) face is not in view of light
      EmitLine(0, 2);
    }

    vN = cross(e4, e5);
    vL = u_oPointLight.vPosition - gs_in[2].vPosition;
    if(dot(vN, vL) <= 0.0) {  // if adjacent (423) not in view of light
      EmitLine(2,4);
    }
    
    vN = cross(e2, e6);
    vL = u_oPointLight.vPosition - gs_in[4].vPosition;
    if(dot(vN, vL) <= 0.0) {  // if adjacent (045) not in view of light
      EmitLine(4, 0);
    }
  }
}
