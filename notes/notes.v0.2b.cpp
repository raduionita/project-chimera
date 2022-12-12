
/** XML ************************************************************************************************************ **/

<app path="/path/to/root/of/the/app"
     name="demoApp01"
     version="0.2b">
  <library>                                           // preloaded stuff
    <model id="copCar02">
    
    </model>
  </library>
  
  <scene type="static|dynamic|???">
    <node type="node">
      <model ref="#copCar02"/>
      <controllers>
        <controller file="/path/to/script.file"/>
      </controllers>
      <node id="root" type="joint">
      
      </node>
    </node>
    
    <node>
      <descriptor />
      <model file="/path/to/model.file" matrix=""> // loads meshes + skeleton in a sub-node structure
        <joint name="root" rid="root" matrix="">
          <joint name="hand">
            <material />                                       // material override
            
            <model file="/path/to/model.file" matrix="position rotation scaling" />
            
          </joint>
        </joint>
      </model>
    </node>
  
    <node type="node"
          id="dog01" 
          class="dog"
          position="x y z"
          orientation="w x y z"
          scale="x y z">
      <model file="/path/to/model.file">                // manager: resource manager for loaded files
        <meshes>
          <mesh id="dogBody">                           // mesh: override defaults for this mesh -->
            <material/>
          </mesh>
          <mesh id="dogColar" />
        </meshes>
        <animations>                                    // animation: it affects all the meshes inside the model
          <animation file="/path/to/animation.file" />
        </animations>
        
        // @todo: current animation pose
      </model>
      
      
      
      <controller/>                                     // controller: dog's ai
    </node>
    
    <node id="fog01" class="">
      <effect id="effect01" ref="effect00" />           // effect: base effect w/ custom stats
    </node>
    
    <node id="lamp01" class="furniture">
      <model>
        <mesh id="lampHead"/>                           // material: transparent, self-illuminated, doesn't cast shadow
        <mesh id="lampBody"/>
      </model>
      
      <light id="lampLight" />                          // controller: bound to #lampHead
      
      <controller/>                                     // controller: lamp button
    </node>
  </scene>
</app>

/** GAME *********************************************************************************************************** **/

class CResourceManager // if a file has been read/loaded, don't reloaded, find it and reuse it

/** NGIN *********************************************************************************************************** **/

class CSkeleton
  # mRoot      : CJoint                     // OR CSkeleton::joint_t
  # mJoints    : std::map<string, CJoint*>
  # mAnimations: std::map<string, CAniamtion*>
  
class CMesh                             // there is no model only a bunch of meshes
  # mMaterial : CMaterial
  
class CAniamtion

class CMaterial

class CLight
  # mIntensity  : vec3  // ambient, diffuse
  # mColor      : vec3  // ngin::rgb == math::vec3
class CAmbientLight
class CDirectLight
class CPointLight
  # mPosition  : vec3
  # mAttenuation: vec3  // k0 (constant) k1 (linear) k2 (quadratic) attenuations
class CSpotLight
  # mPosition  : vec3
  # mAttenuation: vec3  // k0 k1 k2
  # mDirection : vec3
  # mCutoff    : float

/** Notes ********************************************************************************************************** **/

// transparency
  // > IF diffuse map has an alpha channel (rgba texture) => mash has transparency, render after opaque pass
  // > IF material has an opaque/transparency map => mesh has transparency, add to transparent pass 


// rendering
  // > query entities in the fustrum
  // > split drawables into opaque and transparent 
  // > rendering opaque (opaque pass)
    // > order near to far (front to back)
    // > create draw calls 
    // > optimize: try to bundle draw calls/commands togther
    // > optimize: keep track how much of the screen is drawn, don't draw if alread drawn (keep in mind intersecting)
  // > rendering transparent (transparent pass)
    // > order far to near (back to front)
    // > create draw calls
    // > optimize: keep in mind how much of the screen was drawn from the previous pass
    
// research
  // > near to far depth based blending for transparent objects
    