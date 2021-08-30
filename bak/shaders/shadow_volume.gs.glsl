#version 420 core

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PointLight {
  vec3 vPosition;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

layout (triangles_adjacency) in;                // 6 vertices in - 0,2,4(triangle) 1,3,5(adjacency)
layout (triangle_strip, max_vertices = 18) out; // 3(front) + 3(back) + 3 * 4(4 vertices for each triangle edge)

// out gs_out_t {
//   vec3 vColor;
// } gs_out;
uniform mat4 u_mV;
uniform mat4 u_mP;

uniform PointLight u_oPointLight = PointLight(vec3(2.5, 2.5, 2.5));

const float EPSILON = 0.0001;

void EmitQuad(int start, int end) {       // traingle strip
  vec3 vs = gl_in[start].gl_Position.xyz;
  vec3 ve = gl_in[end].gl_Position.xyz;
  vec3 vL;
  
  vL = normalize(vs - u_oPointLight.vPosition);
  gl_Position = u_mP * u_mV * vec4((vs + vL * EPSILON), 1.0); // 1st start vertex - offest inward
  // gs_out.vColor = vec3(0.0, 0.3, 0.0);
  EmitVertex();
  
  gl_Position = u_mP * u_mV * vec4(vL, 0.0); // 2nd start vertex projected at infinity
  // gs_out.vColor = vec3(0.0, 0.3, 0.0);
  EmitVertex();
  
  vL = normalize(ve - u_oPointLight.vPosition);
  gl_Position = u_mP * u_mV * vec4((ve + vL * EPSILON), 1.0); // 3rd end vertex - offset inward
  // gs_out.vColor = vec3(0.0, 0.3, 0.0);
  EmitVertex(); 
  
  gl_Position = u_mP * u_mV * vec4(vL, 0.0); // 4th ending vertex projected at infinity
  // gs_out.vColor = vec3(0.0, 0.3, 0.0);
  EmitVertex();
  EndPrimitive();
}

void main(void) {
  vec3 e1 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;   // 1 ----- 2 -e4-- 3 
  vec3 e2 = gl_in[4].gl_Position.xyz - gl_in[0].gl_Position.xyz;   //  \     / \     /  
  vec3 e3 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;   //  e3   e1  e5  /   
  vec3 e4 = gl_in[3].gl_Position.xyz - gl_in[2].gl_Position.xyz;   //    \ /     \ /    
  vec3 e5 = gl_in[4].gl_Position.xyz - gl_in[2].gl_Position.xyz;   //     0 -e2-- 4     
  vec3 e6 = gl_in[5].gl_Position.xyz - gl_in[4].gl_Position.xyz;   //      \     /      
  //                                                               //       \   e6      
  vec3 vN = cross(e1, e2);                                         //        \ /        
  vec3 vL = u_oPointLight.vPosition - gl_in[0].gl_Position.xyz;    //         5         
  
  vN = normalize(vN);
  vL = normalize(vL);
  
  if(dot(vN, vL) > 0.0) { // if (024) face in view of light
    // render projected quads using light 
    vN = cross(e3, e1);
    if(dot(vN, vL) <= 0.0) { // if adjacent (102) face is not in view of light
      //EmitLine(0, 2);
      EmitQuad(0, 2);
    }

    vN = cross(e4, e5);
    vL = u_oPointLight.vPosition - gl_in[2].gl_Position.xyz;
    if(dot(vN, vL) <= 0.0) {  // if adjacent (423) not in view of light
      //EmitLine(2,4);
      EmitQuad(2,4);
    }

    vN = cross(e2, e6);
    vL = u_oPointLight.vPosition - gl_in[4].gl_Position.xyz;
    if(dot(vN, vL) <= 0.0) {  // if adjacent (045) not in view of light
      //EmitLine(4, 0);
      EmitQuad(4, 0);
    }

    // render front cap
    vL = normalize(gl_in[0].gl_Position.xyz - u_oPointLight.vPosition);             // from Point to Light direction
    gl_Position = u_mP * u_mV * vec4(gl_in[0].gl_Position.xyz - vL * EPSILON, 1.0); // output at Point + offset
    // gs_out.vColor = vec3(0.3, 0.0, 0.0);
    EmitVertex();
    
    vL = normalize(gl_in[2].gl_Position.xyz - u_oPointLight.vPosition);
    gl_Position = u_mP * u_mV * vec4(gl_in[2].gl_Position.xyz - vL * EPSILON, 1.0);
    // gs_out.vColor = vec3(0.3, 0.0, 0.0);
    EmitVertex();
    
    vL = normalize(gl_in[4].gl_Position.xyz - u_oPointLight.vPosition);
    gl_Position = u_mP * u_mV * vec4(gl_in[4].gl_Position.xyz - vL * EPSILON, 1.0);
    // gs_out.vColor = vec3(0.3, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
    
    // render back cap - in reverse winding
    vL = normalize(gl_in[0].gl_Position.xyz - u_oPointLight.vPosition); // from Point to Light direction vector
    gl_Position = u_mP * u_mV * vec4(vL, 0.0);                          // output at infinity using direction vector
    EmitVertex();
    
    vL = normalize(gl_in[4].gl_Position.xyz - u_oPointLight.vPosition);
    gl_Position = u_mP * u_mV * vec4(vL, 0.0);
    EmitVertex();
    
    vL = normalize(gl_in[2].gl_Position.xyz - u_oPointLight.vPosition);
    gl_Position = u_mP * u_mV * vec4(vL, 0.0);
    EmitVertex();
    EndPrimitive();
  }
}
