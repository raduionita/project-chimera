#version 420 core

layout (points) in;
layout (points) out;
layout (max_vertices = 30) out;

in vs_out_t {
  float fType;
  vec3  vPosition;
  vec3  vVelocity;
  float fAge;
} gs_in[];

out float v_fType;
out vec3  v_vPosition;
out vec3  v_vVelocity;
out float v_fAge;

uniform float u_fDeltaTime;
uniform float u_fTime;

uniform float u_fLauncherLifetime;
uniform float u_fPrimaryLifetime;
uniform float u_fSecondaryLifetime;
uniform float u_fTertiaryLifetime;

#define TYPE_LAUNCHER  0.0
#define TYPE_PRIMARY   1.0
#define TYPE_SECONDARY 2.0
#define TYPE_TERTIARY  3.0

uniform sampler1D u_sRandomTex;

vec3 getRandomDirection(float fTexcoord) {
  vec3 vDir = texture(u_sRandomTex, fTexcoord).xyz - vec3(0.5); // [0, 1] - 0.5 = [-0.5, 0.5];
  return vDir;
}

void main(void) {
  float fAge      = gs_in[0].fAge + u_fDeltaTime;
  vec3  vPosition = gs_in[0].vPosition;
  vec3  vVelocity = gs_in[0].vVelocity;
  float fType     = gs_in[0].fType;
  
  if(fType == TYPE_LAUNCHER) {
    if(fAge >= u_fLauncherLifetime) { // if age of launcher has expired
      v_fType     = TYPE_PRIMARY;
      v_vPosition = vPosition;
      vec3 vDir   = getRandomDirection(u_fTime / 1000.0);
      vDir.y = max(vDir.y, 1.0);
      v_vVelocity = normalize(vDir) * 10.0;
      v_fAge      = 0.0;
      EmitVertex();
      EndPrimitive();
      fAge = 0.0;
    }
    
    v_fType     = TYPE_LAUNCHER;
    v_vPosition = vPosition;
    v_vVelocity = vVelocity;
    v_fAge      = fAge;
    EmitVertex();
    EndPrimitive();
  } else {
    vec3 vDeltaPos = (u_fDeltaTime / 1000.0) * vVelocity;
    vec3 vDeltaVel = (u_fDeltaTime / 1000.0) * vec3(0.0, -9.81, 0.0);
    
    if(fType == TYPE_PRIMARY) {
      if(fAge < u_fPrimaryLifetime) {   // primary is ALIVE
        v_fType     = TYPE_PRIMARY;
        v_vPosition = vPosition + vDeltaPos;
        v_vVelocity = vVelocity + vDeltaVel;
        v_fAge      = fAge;
        EmitVertex();
        EndPrimitive();
      } else {                          // primary is DEAD -> split into 10 secondary
        for(int i = 0; i < 10; i++) {
          v_fType     = TYPE_SECONDARY;
          v_vPosition = vPosition;
          vec3 vDir   = getRandomDirection((u_fTime + i) / 1000.0);
          v_vVelocity = normalize(vDir) * 10.0;
          v_fAge = 0.0;
          EmitVertex();
          EndPrimitive();
        }
      }
    } else if(fType == TYPE_SECONDARY) {
      if(fAge < u_fSecondaryLifetime) { // secondary is ALIVE
        if(vPosition.y < 0.0) {
          vPosition.y = 0.0;
          //vVelocity.y = abs(vVelocity.y);
          for(int i = 0; i < 10; i++) {
            v_fType     = TYPE_TERTIARY;
            v_vPosition = vPosition;
            vec3 vDir   = getRandomDirection((u_fTime + i * i) / 1000.0);
            vDir.y      = max(vDir.y, 1.0);
            v_vVelocity = normalize(vDir) * 5.0;
            v_fAge      = 0.0;
            EmitVertex();
            EndPrimitive();
          }
        } else {
          v_fType     = TYPE_SECONDARY;
          v_vPosition = vPosition + vDeltaPos;
          v_vVelocity = vVelocity + vDeltaVel;
          v_fAge      = fAge;
          EmitVertex();
          EndPrimitive();
        }
      } else  {                         // secondary is DEAD
      
      }
    } else {
      if(fAge < u_fTertiaryLifetime) {
        vPosition += vDeltaPos;
        vVelocity += vDeltaVel;
        if(vPosition.y < 0.0) {
          vPosition.y = 0.0;
          vVelocity.y = 0.0;
        }
        v_fType     = TYPE_TERTIARY;
        v_vPosition = vPosition;
        v_vVelocity = vVelocity;
        v_fAge      = fAge;
        EmitVertex();
        EndPrimitive();
      }
    }
  }
}

