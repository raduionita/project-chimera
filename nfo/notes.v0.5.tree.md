# lod: level of detail
# multi mesh models
# multi material or composed materals
# custom materials
# breakable/multi-piece models
# instanced/cacheable/cloned objects (#ref)
# special effects - computed by the gpu (e.g particle systems)
# forces: attractor: gravity
# on great distances render a snapshot(2d) mesh always facing the camera (eg. distant trees, or glass)
# hierarchy meshes
# inverse kinematics (pull the hand to move the elbow)

# ENTITY
# MODEL  : ENTITY:Model
# FORCE  : ENTITY:Force
# CAMERA : ENTITY:Camera
# LIGHT  : ENTITY:Light
# EFFECT : ENTITY:Effect
# BASIC   : ENTITY:Node

# JOINT
------------------------------------------------------------------------------------------------------------------------
```c++
class CNode
  CNode::EScope        mScope;
  std::vector<CEntity> mEntities;
  std::vector<CNode>   mNodes;

class CComponent
  virtual CComponent::EComponent getScope() const = 0;

class TComponent<EComponent::MODEL> : CComponent
  EComponent mType  = {EComponent::MODEL}
  CGeometry*    mGeometry;
  
class CEntity
  CEntity::EScope         mScope;
  std::vector<CComponent> mComponents
  
class CGeometry
  CSkeleton*               mSkeleton;
  CAnimator*               mAnimator;
  CGeometryBuffer*               mGeometryBuffer;
  
class CAnimator
  std::string              mAID;        // something which identifies it among animations 
  CSkeleton*               mSkeleton;   // same as the one inside model - maybe the one inside mode is redundant
  std::vector<CAnimation*> mAnimations; // real owner is CAnimationManager

class CAnimation
  CSkeleton*               mSkeleton;

class CGeometryBuffer
  std::vector<CMesh>       mMeshLoaders;     // meshes are imutable - models own their own meshes
```
------------------------------------------------------------------------------------------------------------------------
```xml
<app>
  <data>
    <entity getType="light" uid="unique id" />
    <!-- when saving most entities go here - the ones in scene are just references -->
    <animation name="" file="" info="for what skeleton?!" />
    <group getType="animation" gid="gid" info="based on skeleton setType">
      <animation aid="#aid" name="" file="" info="for what skeleton?!" />
    </group>
  </data>
  <world getType="voxel|real">
    <node scope="scene">
      <node getType="root" info="unmutable - parent 2 all entities and nodes">
        <entity getType="model" info="OPTIONAL - room or terrain/ground or planet/sun or..." />
      </node>
        <!-- ... -->
    </node> <!-- node:scene -->
    
<!-- multiple scenes -->
    
    <node scope="scene">
      <entity scope="" name="ground" />
      <entity scope="" name="ocean" />
     
<!-- if Toothless drops Hiccup, the node:entity goes to node:scene - Hiccup would be on the ground -->
     
     <!-- THIS LOOKS LIKE THE BEST VERSION SO FAR -->
      <node scope="entity" file="path/to/toothless.xml" matrix="tx ty tz rx ry rz rw sx sy sz">
        <!-- overrides entity model from inside "path/to/nimbus.xml" -->
        <entity scope="model" name="toothless">
          <!-- OR remove the component tag and consider everything inside entity a component on init -->
          <component getType="model" lod="0" file="path/to/toothless.hd.model">
            <model getType="static|dynamic" info="static:rock - dynamic:dog (animated/deformable)">
              <!-- override mesh properties -->
              <mesh name="dragon">
                <material name="black_night_fury" /> <!-- overrides model's meshe materials  -->
              </mesh>
              <mesh name="sadle" />
              <!-- animations can come from an external file or from the model (e.g. collada) -->
              <group getType="animation" gid="#gid" info="loads all animations from that animation group">
                <animation /> <!-- override one of the animations OR add new unique animation only here -->
              </group> <!-- group:animation -->
            </model>
          </component> <!-- component:model -->
          <component getType="model" lod="1" file="path/to/toothless.ld.model"/>
          <component getType="physx"/>
        </entity> <!-- entity:model -->
        
        <node scope="joint" name="sadle" rid="root" matrix="should be same as parent node - probably a pointer"> <!-- OR <node scope="node" OR scope="controller">  -->
          <entity scope="model" ref="#toothless.model" /> <!-- if no reference found postpone it until found -->
          <!-- joint (node) - holds node as data/entity -->
          <entity scope="node">                       <!-- entity element, entity has a node -->
            <component getType="node">
              <node scope="entity">
                <entity getType="model" name="hiccup" />
              </node> <!-- node:entity -->
            </component> <!-- component:node -->
          </entity> <!-- entity:node -->
          
          <node getType="joint" name="tail" rid="relative id to the parent" matrix="deviation from root">
            <entity scope="model" name="a.dumb.cube">
              <component getType="model" shape="cube">
                <model>
                  <mesh matrix="tx ty tz rx ry rz rw sx sy sz">
                    <material name="pink" />
                  </mesh>
                </model>
              </component>
            </entity> <!-- entity:model:shape:cube -->
          </node> <!-- node:joint --> <!-- can only hold other joint getType nodes -->
        </node> <!-- node:joint -->
      </node> <!-- node:entity --> <!-- can only hold joint getType nodes -->
      
      
    </node>
  </world>
</app>
```













