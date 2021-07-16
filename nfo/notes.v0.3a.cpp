
/** **************************************************************************************************************** **/

<scene>
  <node:node> OR <node:main>
    <node:event/>                                         // something happens on collison
  </node:node>
  
  <node:node>
    <node:force name="gravity" />
  </node:node>
  
  <node:node>
    <node:force name="twister">
      <node:model name="twister" />
    </node:force>
  </node:node>

  <node:node matrix="position rotation scaling">
    <node:model>
      <model file="/path/to/model.file" />                // holds model info...
      <node:joint name="root">                            // all children move w/ this node
        <node:model><model file="/path/to/other/sub.model.file" /></node:model>
        <node:light><light type="point" /></node:light>
        <node:effex><effex /></node:effex>                // particle system (sfx) like fire
      </node:joint>
      
      <node:anims>
        <animation name="idle" file="/path/to/animation.file" /> // @see Asset/File/ResourceManager
        <animation name="walk" file="/path/to/animation.file" /> 
      </node:anims>
      
      <node:psyxs />                                             // physics descriptor
    </node:model>
    // what if the model animation/movement affects the sfx somehow?!
    <node:effex>
      
    </node:effex>
  </node:node>
  
  <node:node>
    <node:group>
      <node:model />
      
      <node:model />
      <node:model />
    </node:group>
  </node:node>
</scene>

// game loop //////////////////////////////////////////////////////////////////////////////////////////////////////////

  # while true (the loop)
    # input process 
      # 

    # scene update 
      # for each node in scene
        # if node.type === force (field)
          # node.update (field)
          # query.nodes.in.force(field)
          # send field + nodes in field to physics engine
          # update nodes states after phyxs engine compute
        # else 
          # update node + trigger node->onUpdates() before | node->onUpdated() after
            # for each node in node.nodes (children)
              # update node 
                # animations
                # controllers (scripts, like spin propeller, procedural stuff)
              

    # scene render 
      # for each node in query->scene : nodes in fustrum
        # if node is drawable (+debug mode)
          # render node

// force fields ///////////////////////////////////////////////////////////////////////////////////////////////////////

  // scenario 1: update force node
    // 1.1 for each node in nodes.in.force.field (query nodes in force field)
    // 1.2 apply force to node using physical properies of the node: update position rotation & scaling
    // 1.2.1 apply force to all children of the current node
  
  // scenario 2: update nodes in force field
    // 2.1 for each node in query.fields.using.this.node's.bbox
    // 2.2 for each force field found do 1.2
  
  // scenario 3: separate physics engine
    // 3.1 for force field query nodes inside
    // 3.2 for each node send force + node to physics engine
    // 3.3 update node in scene using the resulting state ... then
  
// colliding objects/nodes ////////////////////////////////////////////////////////////////////////////////////////////

  // ?? if new positions don't have objects intersected but they should have collided
    // ?? how do you actually know if they collided, trajectory ray tracing?
  
// detaching nodes ////////////////////////////////////////////////////////////////////////////////////////////////////

  // nodes that detach/break from parent node, they become different nodes
        
// animations /////////////////////////////////////////////////////////////////////////////////////////////////////////

  // treat animations like controllers (scripts, procedural stuff) that updates the node

// //

/** **************************************************************************************************************** **/

class CScene
  # mList: std::vector<CNode*>
  # mTree: gls::octree<CNode*>

class CNode
  # mType  : EType
  # mNodes : std::vector<CNode*>
  # mParent: CNode*
  # mMatrix: math::mat4*
  # mBBox  : CBBox*               // (re)computed onLoad() + onUpdate()
  # mName  : std::string
  # mUID   : std::atomic<int>     // auto-generated
  # mRID   : std::string
  
class TNode<EType::SCENE> : CNode
class TNode<EType::FORCE> : CNode
class TNode<EType::PSYXS> : CNode
class TNode<EType::MODEL> : CNode
  # mModel : CModel*
class TNode<EType::JOINT> : CNode
  # mJID : std::string
class TNode<EType::ANIMA> : CNode
  # mAnimations : std::map<string, CAnimation*>
class TNode<EType::LIGHT> : CNode
  # mLight : CLight*

/** **************************************************************************************************************** **/

class CModel

class CJoint
  # mChildren : std::array<CJoint*>
  # mParent   : CJoint*

class CSkeleton
  # mRoot : CJoint*

class CAnimation
  # mFrames  : std::array<frame_t*>
  # mSkeleton: skeleton_t*

class CMesh

class CMaterial

class CLight

class CTexture

/** **************************************************************************************************************** **/

// start editor
// create ogl context
// create windows
// open project xml 
// 
