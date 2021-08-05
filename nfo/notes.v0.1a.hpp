namespace game
{
  // play logic | controllers for app objects/entities
  class CMonster
  class CHuman
  class CPlayer : CHuman
}

namespace app
{
  // abstract app objects & structure
  
  class CScene
    # mOctree COctree          // on load: import meshes then calculate | after that on each import recalculate
  
  class CElement
  class CGroup : CElement
    # mItems   std::array<CElement> // elements or groups or groups+elements :)
  
  class CEntity : CElement
    # mPosition   math::vec3   // or model matrix M
    # mComponents std::map<string, IComponent>
    
  class IComponent
    # mType      EType         // IComponent::EType enum
  class TComponent<> : IComponent 

  class CTerrain               // CSurface
  class CWater                 // water + terrain can make a planet 
  
  class CPlanet
  
  class CObject :
    # mLods       std::map<int, CGeometry>         // or mGeometry (start simple)
      // lod 0 : full meshs
      // lod n : (last) (no.anim) 8-sided cylinder w/ different faces (pre-rendered) of the mesh // ray-intersect decides which faces to draw
    # mBbox       CBBox
    # mAnimations std::map<string, CAnimation>

  // checck if model's sub meshes intersect w/ camera's fustrum (in view space)
  
  
}

namespace ogl // graphic engine related classes
{
  class CGeometry                                   // CTerrainModel, CGeometryModel, CIntstancedModel
    # mMeshes std::map<string, CMesh>            // string (name of the part)
    # // + vao info                              // vbo (buffer range)
    
    
  class CMesh                                    // simple class/object holding triangle data
    # mVertexBufferRange                         // vbo
    # mIndexBufferRange                          // ebo
    # mMaterial

  class BMaterial

  class CTexture                                 // CMapTexture vs CPerlinTexture
  
  class CPerlinTexture : CTexture                // distance to camera | has a cache (or multiple)
    # mCache

  class CLight 
  class CDirectLight : CLight
  class CPointLight  : CLight
  class CSpotLight   : CLight

  class CAnimation
  
  class CProgram
  
  class CShader
  
  class CCamera
}

<scene>
  <model/>      // element
  <light/>      // element
  <effect/>     // element
  <controller\>


// test cases /////////////////////////////////////////////////////////////////////////////////////////////////////////

  // zombie
    // position
    // model
      // skeleton
      // meshes

  // car
    // position...
    // model (lod0)
      // skeleton
      // mesh 0: (chassis)
        // material (metalic shader 0)
      // mesh 1: (door 0)
        // material (metalic shader 2) 
      // mesh 2: (window 0)
    // skeleton
      // animations
    // controller
    // effect
    

  // bottle
    // position, orientation (ratation), scale = model matrix
    // model
      // mesh 0: bottle
        // material
          // diffuse: texture w/ transparency
      // mesh 1: cap
        // material

  // ambient light    // from sunlight
    // position...
    // bbox (minux internal bboxes - inside closed buildings)
    // light

  // smoke snek
    // position...
    // effect(s)      // along a curve (bezier)
    // controller (smoke descriptor - phase manager)
    // bbox           // collider (convex wrapper)
  
  // fog | dust cloud
    // position...
    // effect (particle system, screen space effect or 3d volumentric texture)
    // controller (time to live | lifespan)

  // dust cloud
    // position...
    // effect (particle system)
    // controller (particle behaviour)
    
  // river
    // position...
    // model
      // mesh
        // material     // dynamic, the river texture moves (river flow)
    // effect(s)
    // displacement map for when something creates waves

  // campfire
    // position...
    // model (wood)
    // effect (particle system)
    // light (point)
    // controller (lifespan)

  // fire (effect)
    // position
    // light (point light)
    // effect (particle system)

  // flashlight
    // position
    // model
    // light (spot light)   // bound to this mesh
    // controller (button)  // can switch the light on and off

  // robot (drawable) (dynamic) (animated)
    // position, rotation, scale (for view matrix)
    // model
      // skeleton
      // mesh(s)          // <- + CMeshManager | CGeometryManager
        // material(s)    // <- + CMaterialManager
    // animations         // <- + CAnimationManager
    // light(s)           // bound to one of the meshes or the skeleton
    // bbox               // gets updated by the animation, position, rotation, scaling 
  
  // tree (drawable) (static) (animated)
    // position, rotation, scale (for view matrix)
    // model
      // mesh
        // material
    // controller         // for the leaves - mesh (cloned) or effect (particle system, or both)
  
  // chair (drawable) (dynamic)
    // position, rotation, scale (for view matrix)
    // model
      // mesh
        // material
    // bbox

  // grass (drawable) 
    // position, rotation, scale (for view matrix)
    // model (base model that will be cloned)
      // mesh
        // material
    // placement map(s) | P (vec3) R (vec4) S (vec3) matrix map(s)
    // burn|wet|freeze map (when something happens to a portion of the map) | this map is updateable (fire grows)
    // bend map OR points (where grass bends) (get from engine update) | the bend map is updateable w/ time it fades

  // terrain (drawable) (static)
    // position, rotation, scale (for view matrix)
    // model (plane: procedural or mesh)
      // mesh
        // material
          // displacement map (texture or noise map)
    
  // planet (drawable) (dynamic)      // spherical terrain?!
    // position, rotation, scale (for view matrix)
    // model 
      // mesh (tessellate w/ camera distance)
        // material
          // displacement map (noise map|texture)
    // tessellate mesh needs to be extracted for physics sim. 
    
    
// game/physics update
  // update all positions (just positions for now)
  // check/collect intersections (collisions)
  // eval collisions to new positions
  // recheck (new) intersections (collisions)
  
  
// render update/loop
  // order far to near
  // find intersecting objects (for proper render order)
  
