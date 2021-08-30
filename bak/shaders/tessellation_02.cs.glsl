#version 420 core

layout (vertices = 1) out;

uniform float u_fTessLevel;

in vs_out_t {
  vec3 vPosition; // model space
  vec2 vTexcoord; // model space
  vec3 vNormal;   // model space
  vec3 vTangent;  // model space
} cs_in[];

struct cs_patch_t {
  vec3 vB030;
  vec3 vB021;
  vec3 vB012;
  vec3 vB003;
  vec3 vB102;
  vec3 vB201;
  vec3 vB300;
  vec3 vB210;
  vec3 vB120;
  vec3 vB111;
  vec2 vTexcoord[3];
  vec3 vNormal[3];
  vec3 vTangent[3];
};

out patch cs_patch_t cs_patch;

vec3 projectToPlane(vec3 point, vec3 planePoint, vec3 planeNormal) {
  vec3  v = point - planePoint;   // vector from plane center to vertex
  float l = dot(v, planeNormal);  // length of the projection of v on the normal
  vec3  d = l * planeNormal;      // projected vector on the normal
  //return normalize(vec3(1.0));
  return (point - d);             // projected vector on the plane
}

void computeControlPoints() {
  cs_patch.vB030 = cs_in[0].vPosition; // original vertices stay the same
  cs_patch.vB003 = cs_in[1].vPosition;
  cs_patch.vB300 = cs_in[2].vPosition;
  
  vec3 vE300 = cs_patch.vB003 - cs_patch.vB030; // edges
  vec3 vE030 = cs_patch.vB300 - cs_patch.vB003;
  vec3 vE003 = cs_patch.vB030 - cs_patch.vB300;
  
  // generate 2 midpoints on each edge
  cs_patch.vB021 = cs_patch.vB030 + vE300 * 1.0 / 3.0; 
  cs_patch.vB012 = cs_patch.vB030 + vE300 * 2.0 / 3.0;
  cs_patch.vB102 = cs_patch.vB003 + vE030 * 1.0 / 3.0;
  cs_patch.vB201 = cs_patch.vB003 + vE030 * 2.0 / 3.0;
  cs_patch.vB210 = cs_patch.vB300 + vE003 * 1.0 / 3.0;
  cs_patch.vB120 = cs_patch.vB300 + vE003 * 2.0 / 3.0;
  
  // project each midpoint on a plane defined by the nearest vertex and its normal
  cs_patch.vB021 = projectToPlane(cs_patch.vB021, cs_patch.vB030, cs_patch.vNormal[0]);
  cs_patch.vB012 = projectToPlane(cs_patch.vB012, cs_patch.vB003, cs_patch.vNormal[1]);
  cs_patch.vB102 = projectToPlane(cs_patch.vB102, cs_patch.vB003, cs_patch.vNormal[1]);
  cs_patch.vB201 = projectToPlane(cs_patch.vB201, cs_patch.vB300, cs_patch.vNormal[2]);
  cs_patch.vB210 = projectToPlane(cs_patch.vB210, cs_patch.vB300, cs_patch.vNormal[2]);
  cs_patch.vB120 = projectToPlane(cs_patch.vB120, cs_patch.vB030, cs_patch.vNormal[0]);
  
  // center cp
  vec3 vCenter = (cs_patch.vB003 + cs_patch.vB030 + cs_patch.vB300) / 3.0;
  cs_patch.vB111  = (cs_patch.vB021 + cs_patch.vB012 + cs_patch.vB102 +
                     cs_patch.vB201 + cs_patch.vB210 + cs_patch.vB120) / 6.0;
  cs_patch.vB111 += (cs_patch.vB111 - vCenter) / 2.0;
}

void main(void) {
  for(int i = 0; i < 3; i++) {
    cs_patch.vTexcoord[i] = cs_in[i].vTexcoord;
    cs_patch.vNormal[i]   = cs_in[i].vNormal;
    cs_patch.vTangent[i]  = cs_in[i].vTangent;
  }
  
  computeControlPoints();
  
  // calculate tessellation levels
  gl_TessLevelOuter[0] = u_fTessLevel;
  gl_TessLevelOuter[1] = u_fTessLevel;
  gl_TessLevelOuter[2] = u_fTessLevel;
  gl_TessLevelInner[0] = u_fTessLevel;
}
