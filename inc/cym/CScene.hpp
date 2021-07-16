#ifndef __cym_cscene_hpp__
#define __cym_cscene_hpp__

#include "sys/CPointer.hpp"
#include "sys/CBlock.hpp"
#include "sys/CException.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CModel.hpp"
#include "cym/CLight.hpp"
#include "glm/glm.hpp"
#include "glm/CFrustum.hpp"
#include "glm/CAABB.hpp"
#include "glm/CQuaternion.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CTransform.hpp"

#include <array>

namespace cym {
  class CScene; class IScene;
  class CNode; 
  class CCell; 
  class COctree; 
  class CQuery;
  class CResult; 
  
  class CSceneLoader; template<typename T> class TSceneLoader;
  
  class CSceneManager;
  
  // nodes ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CNode {
      friend class CScene;
      friend class CCell;
      friend class COctree;
      friend class CQuery;
      friend class CResult;
      typedef cym::name node_name;
      typedef cym::name name_t;
      typedef uint id_t;
    public:
      enum EType { NONE = -1, BASIC = 0, DEBUGABLE = BASIC, JOINT, SCENE, TREE = SCENE, ENTITY, LIGHT, CAMERA, FORCE, DRAWABLE, MODEL = DRAWABLE+1, EMITTER = DRAWABLE+2 };
    private:
      static id_t                       sID;
    protected:
      id_t                              mID {sID++};
      bool                              mDirty {true}; // = something changed
      cym::name                         mName;
      glm::aabb                         mAABB;
      glm::xform                        mTransform;
      std::map<name_t, sys::spt<CNode>> mNodes;
      /* parent, if null => root node */
      sys::wpt<CNode>                   mRoot;
    public:
      CNode(const cym::name& tName, const glm::aabb& tAABB, const glm::xform& tXform=0) : mName{tName}, mAABB{tAABB}, mTransform{tXform} { }
      CNode(const cym::name& tName,                         const glm::xform& tXform=0) : mName{tName}, mAABB{0}, mTransform{tXform} { }
      virtual ~CNode() { CYM_LOG_NFO("cym::CNode::~CNode()::" << this << " NAME:" << mName); }
    public:
      friend std::ostream& operator <<(std::ostream&, const CNode&);
      friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CNode&);
    public:
      /* test type of node */
      virtual inline bool isBasic()     const { return false; }
      virtual inline bool isDebugable() const { return false; }
      virtual inline bool isJoint()     const { return false; }
      virtual inline bool isScene()     const { return false; }
      virtual inline bool isEntity()    const { return false; }
      virtual inline bool isLight()     const { return false; }
      virtual inline bool isCamera()    const { return false; }
      virtual inline bool isForce()     const { return false; }
      virtual inline bool isDrawable()  const { return false; }
      virtual inline bool isModel()     const { return false; }
      virtual inline bool isEmitter()   const { return false; }
      /* for TNode<CNode::EType> conversion */
      virtual inline EType getType() const { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
      /* this node's name */
      inline const cym::name& getName() const { return mName; }
      /* is dirty */
      inline bool isDirty() const { return !isRoot() && (mRoot->isDirty() && mDirty); }
      /* rootless/baseless? */
      inline bool isRoot() const { return mRoot == nullptr; }
      /* return 1st level child nodes */
      inline const decltype(mNodes)& getNodes() const { return mNodes; }
      /* get absolute AABB */
      inline const glm::aabb getAABB() const { return  /* getMatrix() * */ mAABB; }
      /* get model matrix for this node */
      inline const glm::mat4 getMatrix()         const { return getAbsoluteMatrix(); }
      inline const glm::mat4 getAbsoluteMatrix() const { return (isRoot()) ? (getRelativeMatrix()) : (mRoot->getAbsoluteMatrix() * getRelativeMatrix()); }
      inline const glm::mat4 getRelativeMatrix() const { return mTransform.toMatrix(); }
// @todo: this should return a transform w/ parent's transform included // transform structure =(position,orientation,scale) */
      inline const glm::xform& getTransform() const { return mTransform; }
      /* get node's absolute position  */
      inline const glm::vec3 getPosition()         const { return getAbsolutePosition(); }
      inline const glm::vec3 getAbsolutePosition() const { return (isRoot()) ? (getRelativePosition()) : (mRoot->getAbsolutePosition() + getRelativePosition()); }
      inline const glm::vec3 getRelativePosition() const { return mTransform.position; }
      /* get node's absolute orientation  */
      inline const glm::quat getOrientation()         const { return getAbsoluteOrientation(); }
      inline const glm::quat getAbsoluteOrientation() const { return (isRoot()) ? (getRelativeOrientation()) : (mRoot->getAbsoluteOrientation() * getRelativeOrientation()) ; }
      inline const glm::quat getRelativeOrientation() const { return mTransform.orientation; }
      /* get node's absolute scale  */
      inline const glm::vec3 getScale()         const { return getAbsoluteScale(); }
      inline const glm::vec3 getAbsoluteScale() const { return (isRoot()) ? (getRelativeScale()) : (mRoot->getAbsoluteScale() * getRelativeScale()) ; }
      inline const glm::vec3 getRelativeScale() const { return mTransform.scale; }
      /* returns the root/parent of this node */
      inline const decltype(mRoot)& getRoot() const { return mRoot; }
    public: // as parent 
      /* attach tNode to this, add to mNodes and extend this.mAABB */
      void            push(sys::spt<CNode> tNode);
      /* pop CNode by name, and return it */
      sys::spt<CNode> pull(const cym::name& tName);
    public: // as child
      /** detach from current parent => rootless node */
      void yield();
      /** cling this to a parent (tParent::push(this)) */
      void cling(sys::spt<CNode> tParent);
      /** from one parent (this.mRoot) to another parent (tParent) */
      void shift(sys::spt<CNode> tParent);
      /** extend this.mAABB (and all its ancestors) by tAABB  */
      void extend(const glm::aabb& tAABB);
      /** rebuild this.mAABB (and all its ancestors) using children's mAABBs  */
      bool shrink();
  };
  
  template<CNode::EType T> class TNode : public CNode {
    public:
      virtual inline EType getType() const override { return T; }
  };
  
// @todo: transform node from basic to joint 
  template<> class TNode<CNode::BASIC> : public CNode {
    public:
      using CNode::CNode;
    public:
      virtual inline bool isBasic() const override final { return true; }
      virtual inline bool isDebugable() const override final { return true; }
      virtual inline CNode::EType getType() const override { return CNode::BASIC; }
  };
  
  template<> class TNode<CNode::JOINT> : public TNode<CNode::BASIC> {
    protected:
    //sys::wptr<CJoint> mJoint; // link to real joint  
    public:
      using TNode<CNode::BASIC>::TNode;
    public:
      virtual inline bool isJoint() const override final { return true; }
      virtual inline CNode::EType getType() const override { return CNode::JOINT; }
  };
  
  template<> class TNode<CNode::SCENE> : public TNode<CNode::BASIC> {
    public:
      using TNode<CNode::BASIC>::TNode;
    public:
      virtual inline bool isScene() const override final { return true; }
      virtual inline CNode::EType getType() const override { return CNode::SCENE; }
  };
  
  template<> class TNode<CNode::ENTITY> : public CNode {
    public:
      using CNode::CNode;
    public:
      virtual inline bool isEntity() const override final { return true; }
      virtual inline CNode::EType getType() const override { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
  };
  
  template<> class TNode<CNode::LIGHT> : public TNode<CNode::ENTITY> {
    protected:
      // sys::sptr<ILight> mLight;
        // type = POINT/OMNI, DIRECT, SPOT, AREA
          // type = POINT
            // position == glm::vec3 (POINT,SPOT)
            // k0,k1,k2 = float      (POINT,SPOT)
            // direction = glm::vec3 (DIRECT,SPOT)
            // cutoff = float        (SPOT)
        // color = glm::vec3
        // ambient intesity = float
        // diffuse intensity = float
    public:
      virtual inline bool  isLight() const override final { return true; }
      virtual inline EType getType() const override final { return CNode::LIGHT; }
      
      // ogl geometry (for debugcall)
      //       // basically, 3-line-star-ish "geometry" 
      //       float vertices[] = {
      //         -0.25f, 0.0f,   0.0f, 
      //          0.25f, 0.0f,   0.0f, 
      //           0.0f,-0.25f,  0.0f, 
      //           0.0f, 0.25f,  0.0f, 
      //           0.0f,  0.0f,-0.25f, 
      //           0.0f,  0.0f, 0.25f };
      //          
      //       glGenBuffers(1, &mVBO);
      //       glBindBuffer(GL_ARRAY_BUFFER, mVBO);
      //       glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
      //       
      //       glGenVertexArrays(1, &mVAO);
      //       glBindVertexArray(mVAO);
      //       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)((0) * sizeof(GLfloat)));
      //       glEnableVertexAttribArray(0);
      
      // on debugcall
      //       glBindVertexArray(mVAO);
      //       glBindBuffer(GL_ARRAY_BUFFER, mVBO);
      //       
      //       glEnable(GL_POLYGON_OFFSET_LINE);
      //       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      //       glLineWidth(2.0f);
      //       
      //       bool bDepthTest = glIsEnabled(GL_DEPTH_TEST);
      //       bool bStencilTest = glIsEnabled(GL_STENCIL_TEST);
      //       if(bDepthTest)
      //         glDisable(GL_DEPTH_TEST);
      //       if(bStencilTest)  
      //         glDisable(GL_STENCIL_TEST);
      //         
      //       glDrawArrays(GL_LINES, 0, 6);
      //       
      //       if(bDepthTest)
      //         glEnable(GL_DEPTH_TEST);
      //       if(bStencilTest)  
      //         glEnable(GL_STENCIL_TEST);
      // 
      //       glBindVertexArray(0);
      //       
      //       glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      //       glDisable(GL_POLYGON_OFFSET_LINE);
  };
  
  template<> class TNode<CNode::CAMERA> : public TNode<CNode::ENTITY> {
    protected:
    //sys::sptr<ICamera> mCamera;
    public:
      virtual inline bool isCamera() const override final { return true; }
      virtual inline EType getType() const override final { return CNode::CAMERA; }
    public: // actions

  };
  
  template<> class TNode<CNode::FORCE> : public TNode<CNode::ENTITY> {
    protected:
    //force descriptor
    public:
      virtual inline bool isForce() const override final { return true; }
      virtual inline CNode::EType getType() const override { return CNode::FORCE; }
  };
  
  template<> class TNode<CNode::DRAWABLE> : public TNode<CNode::ENTITY> {
    public:
      using TNode<CNode::ENTITY>::TNode;
    public:
      virtual inline bool isDrawable() const override final { return true; }
      virtual inline CNode::EType getType() const override { throw sys::exception("NOT IMPLEMENTED",__FILE__,__LINE__); }
  };
  
  template<> class TNode<CNode::MODEL> : public TNode<CNode::DRAWABLE> {
    protected:
      sys::spt<IModel> mModel;
    public:
      using TNode<CNode::DRAWABLE>::TNode;
      TNode(sys::spt<IModel> tModel) : TNode<CNode::DRAWABLE>(sys::string{"model"}+tModel->getName(), tModel->getAABB()), mModel{tModel} { }
      TNode(const cym::name& tName, sys::spt<IModel> tModel) : TNode<CNode::DRAWABLE>(tName, tModel->getAABB()), mModel{tModel} { }
    public:
      virtual inline bool isModel() const override final { return true; }
      virtual inline CNode::EType getType() const override { return CNode::MODEL; }
    public:
      inline void             setModel(sys::spt<IModel> tModel) { mModel = tModel; mAABB = tModel->getAABB(); }
      inline decltype(mModel) getModel() const { return mModel; }
  };
  
  template<> class TNode<CNode::EMITTER> : public TNode<CNode::DRAWABLE> {
    protected:
    // emitter descriptor
    public:
      using TNode<CNode::DRAWABLE>::TNode;
    public:
      virtual inline bool isEmitter() const override final { return true; }
      virtual inline CNode::EType getType() const override { return CNode::EMITTER; }
  };
  
  inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CNode& node) {
    std::ostringstream oss;
    
    static uint tSpaces = 0;
    
    oss << "node:";
  
    switch (node.getType()) {
      case CNode::BASIC  : oss << "basic";  break;
      case CNode::JOINT  : oss << "joint";  break;
      case CNode::SCENE  : oss << "scene";  break;
      case CNode::ENTITY : oss << "entity"; break;
      case CNode::MODEL  : oss << "model";  break;
      case CNode::LIGHT  : oss << "light";  break;
      case CNode::CAMERA : oss << "camera";  break;
      case CNode::FORCE  : oss << "force";  break;
      case CNode::EMITTER: oss << "emitter";  break;
      default: oss << (uint)(node.getType()); break;
    }
    
    oss << '@' << node.getName() << '#' << node.mAABB << 'n' << node.mNodes.size();
    
    for (auto it = node.mNodes.begin(); it != node.mNodes.end(); ++it) {
      oss << '\n' << std::string(tSpaces++, ' ') << 'L' << *(it->second);
      tSpaces--;
    }
    
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }
  
  inline std::ostream& operator <<(std::ostream& out, const CNode& node) {
    static uint tSpaces = 0;
    
    out << "node:";
  
    switch (node.getType()) {
      case CNode::BASIC  : out << "basic";  break;
      case CNode::JOINT  : out << "joint";  break;
      case CNode::SCENE  : out << "scene";  break;
      case CNode::ENTITY : out << "entity"; break;
      case CNode::MODEL  : out << "model";  break;
      case CNode::LIGHT  : out << "light";  break;
      case CNode::CAMERA : out << "camera";  break;
      case CNode::FORCE  : out << "force";  break;
      case CNode::EMITTER: out << "emitter";  break;
      default: out << (uint)(node.getType()); break;
    }
    
    out << '@' << node.getName() << '#' << node.mAABB << 'n' << node.mNodes.size();
    
    for (auto it = node.mNodes.begin(); it != node.mNodes.end(); ++it) {
      out << '\n' << std::string(tSpaces++, ' ') << 'L' << *(it->second);
      tSpaces--;
    }
    
    return out;
  }
  
  // tree ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CResult {
      friend class CScene;
      friend class COctree;
      friend class CCell;
      friend class CQuery;
    protected:
      sys::vector<sys::spt<TNode<CNode::SCENE>>> mNodes;
    public:
      /* return found nodes */
      inline const decltype(mNodes)& getNodes() const { return mNodes; }
      /* return found drawable (model,emitter) nodes */
      inline const sys::vector<sys::spt<TNode<CNode::DRAWABLE>>> getDrawableNodes() {
        sys::vector<sys::spt<TNode<CNode::DRAWABLE>>> tDrawables;
        // for each node:scene in mNodes -> for each node:? in node:scene  
        for (auto& tNode : mNodes) for (auto& [tName,tChild] : tNode->mNodes) if (tChild->isDrawable()) {
          tDrawables.push_back(sys::static_pointer_cast<TNode<CNode::DRAWABLE>>(tChild)); 
        }
        return tDrawables;
      }
      /* return found model nodes */
      inline const sys::vector<sys::spt<TNode<CNode::MODEL>>> getModelNodes() {
        sys::vector<sys::spt<TNode<CNode::MODEL>>> tModels;
        for (auto& tNode : mNodes) for (auto& [tName,tChild] : tNode->mNodes) if (tChild->isModel()) {
          tModels.push_back(sys::static_pointer_cast<TNode<CNode::MODEL>>(tChild)); 
        } 
        return tModels;
      }
      /* return found nodes models */
      inline const sys::vector<sys::spt<IModel>> getModels() {
        sys::vector<sys::spt<IModel>> tModels;
        for (auto& tNode : mNodes) for (auto& [tName,tChild] : tNode->mNodes) if (tChild->isModel()) {
          auto tModel = sys::static_pointer_cast<TNode<CNode::MODEL>>(tChild);
          tModels.push_back(tModel->getModel()); 
        }
        return tModels;
      }
  };
  
  class CQuery {
      friend class CScene;
      friend class COctree;
      friend class CCell;
      friend class CResult;
    public:
      using ENode = CNode::EType;
      enum EOrder { NONE = -1, FRONT_TO_BACK, FB = FRONT_TO_BACK, BACK_TO_FRONT, BF = BACK_TO_FRONT, };
    public:
      sys::spt<glm::frustum> mFrustum; // defaults to empty = not ued
      EOrder                 mOrder {CQuery::NONE};
      ENode                  mType  {CNode::BASIC};
      int                    mLimit {-1};
    private:
      sys::spt<CResult> mResult;
    public:
      CQuery() : mResult{new CResult} { }
      CQuery(const glm::frustum& tFrustum) : mFrustum{new glm::frustum{tFrustum}}, mResult{new CResult} { }
      ~CQuery() = default;
    public:
      inline bool                hasFrustum() const { return mFrustum != nullptr; }
      inline const glm::frustum& getFrustum() const { return *mFrustum; }
      inline EOrder              getOrder()   const { return mOrder; }
      inline ENode               getType()    const { return mType; }
      inline int                 getLimit()   const { return mLimit; }
  };
  
// @todo: class CData { enum class EType : uint { MAIN = 0, LEFT, DOWN, BACK, RIGHT, TOP, FRONT, } };
  // +-----------------------DATA
  // |  +-------DATA         |
  // |  | +---+ | +---CELL   |
  // |  | | C | | | C |      |
  // |  | +---+ | +---+      |
  // | +--------|-------DATA |
  // | || +---+ | +---+ |    |
  // | || | C | | | C | |    | 
  // | || +---+ | +---+ |    |
  // | |+-------+     D |    |
  // | +----------------+  D |
  // +-----------------------+
  
  class CCell {
      friend class CNode;
      friend class COctree;
      friend class CScene;
      friend class CQuery;
      friend class CResult;
    public:
       enum EType { LDB/*left-down-back*/=0, RDB, LTB, RTB, LDF, RDF, LTF, RTF/*right-top-front*/, ROOT=9};
    protected:
      static constexpr EType kTypes[8] { LDB/*0*/, RDB/*1*/, LTB/*2*/, RTB/*3*/, LDF/*4*/, RDF/*5*/, LTF/*6*/, RTF/*7*/ };
      static constexpr uint  kMaxDepth {128}; // max 128 cells deep  
    protected:
      uint                                       mDepth {0};
      EType                                      mType;
      glm::aabb                                  mAABB;
// @todo: glm::aabb mRelative (to the parent) = max aabb , mAbsolute = (to the nodes) = min aabb (just wrapping the nodes);
// @todo: octree space (an 1/8th) needs:
  // -> mMaxAABB // AABB from splitting (assigned on creation, from parent)
  // -> mMinAABB // AABB from elements inside it (min CONNOT be > max), like an element bounding box
      sys::wpt<CCell>                            mRoot;
      sys::array<sys::spt<CCell>,8>              mCells; // 1/8th of aabb // main, top, DOWN, front, back, left, right
      sys::vector<sys::spt<TNode<CNode::SCENE>>> mNodes;   // data (if too big for children & too small for this.mParent
// @todo: multiple LEAVES: sys::array<sys::spt<CLeaf>,7> mLeaves; // hold data
    protected:
      /* create root-level cell, depth = 0 */
      CCell();
      /* create child cell, w/ type, calculate aabb based on type */
      CCell(sys::wpt<CCell> tRoot, EType tType);
      /* create child cell, w/ pre-calculated aabb */
      CCell(sys::wpt<CCell> tRoot, const glm::aabb& tAABB, EType tType);
    public:
      ~CCell() = default;
    public:
      friend std::ostream& operator <<(std::ostream&, const CCell&);
      friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CCell& cell);
    public:
      inline bool isRoot() const { return mRoot == nullptr; /*OR mType == EType::ROOT*/ }
      inline const decltype(mNodes)& getNodes() const { return mNodes; }
      inline const glm::aabb& getAABB() const { return mAABB; }
    public:
      /* pull&return all nodes from self & all children, used when extending root's AABB */
      sys::vector<sys::spt<TNode<CNode::SCENE>>> cull();
      /* push tNode to this cell (or its children), tForce it if already compared AABB's */
      void push(sys::spt<TNode<CNode::SCENE>> tNode, bool tForce = false);
      /* find scene nodes using a CQuery + glm::frustum */
      sys::spt<CResult> find(const CQuery& tQuery);
  };
  
  inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CCell& cell) {
    std::ostringstream oss;
    static uint tSpaces = 0;
    
    oss << "cell@" << cell.mType << 'd' << cell.mDepth << '#' << cell.mAABB << 'n' << cell.mNodes.size(); 
    
    for (auto& tCell : cell.mCells) if (tCell) {
      oss << '\n' << std::string(tSpaces++, ' ') << 'L' << *(tCell);
      tSpaces--;
    }
    
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }
  
  inline std::ostream& operator <<(std::ostream& out, const CCell& cell) {
    static uint tSpaces = 0;
    
    out << "cell@" << cell.mType << 'd' << cell.mDepth << '#' << cell.mAABB << 'n' << cell.mNodes.size(); 
    
    for (auto& tCell : cell.mCells) if (tCell) {
      out << '\n' << std::string(tSpaces++, ' ') << 'L' << *(tCell);
      tSpaces--;
    }
    
    return out;
  }
  
// @todo: CCellManager need something to re-use cells (so u don't keep allocating memory)
  
  // scene ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CScene : public cym::CResource {
      friend class IScene;
      friend class CSceneLoader;
      friend class CSceneManager;
      using ENode = CNode::EType;
    protected:
      sys::spt<cym::TNode<CNode::BASIC>> mNode;
      sys::spt<cym::CCell>               mCell;
    public:
      CScene(const cym::name& tName = "default");
      CScene(sys::spt<CSceneLoader>);
      ~CScene();
    public:
      friend std::ostream& operator <<(std::ostream&, const CScene&);
      friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CScene&);
    public:
      /* return the root node (never null) */
      inline sys::spt<CNode> getRoot() const { return mNode; }
    public:
      /* load using a loader */
      virtual void load(sys::spt<CSceneLoader>) final;
    public: // actions
      /* add model to scene through a node, return the node:scene owner */
      sys::spt<TNode<CNode::SCENE>> push(sys::spt<IModel>, const glm::xform& = 0.0);
      /* find scene nodes using a CQuery + glm::frustum */
      sys::spt<CResult> find(const CQuery&);
      
// @todo: sys::sptr<TNode<ENode::SCENE>> push(sys::sptr<ILight> tLight); // camera, force, emitter,

  };
  
  inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CScene& scene) {
    std::ostringstream oss;
    oss << "scene:" << '\n';
    oss << ".node:" << '\n';
    oss << *(scene.mNode);
    oss << '\n';
    oss << ".cell:" << '\n';
    oss << *(scene.mCell);
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }
  
  inline std::ostream& operator <<(std::ostream& out, const CScene& scene) {
    out << "scene:" << '\n';
    out << ".node:" << '\n';
    out << *(scene.mNode);
    out << '\n';
    out << ".cell:" << '\n';
    out << *(scene.mCell);
    return out;
  }
  
  // instances ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class IScene : public cym::TInstance<CScene> {
      friend class CScene;
      friend class CInstanceRegistry;
    public:
      using cym::TInstance<CScene>::TInstance;
    public:
      friend std::ostream& operator <<(std::ostream& out, const IScene& scene);
    public:
      inline CScene&          getScene() const { return mInstance.raw(); }
      inline sys::sptr<CNode> getRoot() const  { return mInstance->getRoot(); }
    public:
      /* add model to scene through a node, return the node:scene owner */
      inline sys::spt<TNode<CNode::SCENE>> push(sys::spt<IModel> tModel, const glm::xform& tForm = 0) { return mInstance->push(tModel, tForm); }
      /* find scene nodes using a CQuery + glm::frustum */
      inline sys::spt<CResult> find(const CQuery& tQuery) { return mInstance->find(tQuery); }
  };
  
  inline std::ostream& operator <<(std::ostream& out, const IScene& scene) {
    return out << scene.getResource();
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CSceneLoader : public CResourceLoader {
      friend class CScene;
      friend class CSceneManager;
    public:
      using CResourceLoader::CResourceLoader;
      inline CSceneLoader(const cym::name& tName) : CResourceLoader(tName) { CYM_LOG_NFO("cym::CSceneLoader::CSceneLoader(cym::name&)::" << this);  }
      inline ~CSceneLoader() { CYM_LOG_NFO("cym::CSceneLoader::~CSceneLoader()::" << this); }
    public:
      virtual inline void load(sys::sptr<CResourceLoader>) { throw sys::exception("CSceneLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      template<typename T> inline static sys::sptr<TSceneLoader<T>> from(const T& tSource) { return new TSceneLoader<T>{tSource}; }
      template<typename T, typename... Args> inline static cym::name name(const T& tSource, Args&&... args) { return TSceneLoader<T>::name(tSource, std::forward<Args>(args)...); }
  };
  
  template<typename T> class TSceneLoader : public CSceneLoader { };
  
  template<> class TSceneLoader<sys::CFile> : public CSceneLoader {
      friend class CModelCodec;
    protected:
      sys::CFile mFile;
    public:
      inline TSceneLoader(const sys::CFile& tFile) : CSceneLoader(tFile.path()), mFile{tFile} { };
    public:
      inline static cym::name name(const sys::CFile& tFile) { return tFile.path(); }
      virtual void load(sys::sptr<CResourceLoader>) override;
    public:
      inline sys::CFile& getFile() { return mFile; }
  };
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: CEntityManager
  
  class CSceneManager : public cym::TManager<CScene>, public sys::TSingleton<CSceneManager> {
      friend class CScene;
      friend class CSceneLoader;
    protected:
      sys::map<cym::name,sys::spt<CScene>> mScenes;
    public:
      CSceneManager();
      ~CSceneManager();
    public:
      static void save(sys::spt<CScene> pScene) {
        static auto pThis {cym::CSceneManager::getSingleton()};
        CYM_LOG_NFO("cym::CSceneManager::save(sys::sptr<CScene>)::" << pThis);
        pThis->mScenes.insert(std::pair(pScene->mName, pScene));
      }
      
      static sys::spt<CScene> load(sys::spt<CSceneLoader> pSceneLoader) {
        static auto self {cym::CModelManager::getSingleton()};
        CYM_LOG_NFO("cym::CSceneManager::load(sys::sptr<CSceneLoader>)::" << self);
        
        if (!pSceneLoader) return nullptr;
        
        sys::sptr<CScene> pScene {new CScene{pSceneLoader->getName()}};
        
        sys::async([pScene, pSceneLoader](){
          
          // loads using codes or other TSceneLoader::load() 
          pSceneLoader->load(pSceneLoader);
          
          // process additional stuff (sub loaders)
// @todo: something here?! (ex: for CModel sub-meshes are loaded)
          
          // finaly load everyting into pScene
          pScene->load(pSceneLoader);
          
        }, sys::EAsync::SPAWN);
        
        CSceneManager::save(pScene);
        
        return pScene;
      }
      
      //template<typename T, typename... Args> static sys::sptr<IScene> load(const T& tSource, Args&&... args) {
      static sys::spt<IScene> load(const sys::CFile& tSource) {
        static auto pThis {cym::CSceneManager::getSingleton()};
        CYM_LOG_NFO("cym::CSceneManager::load(T&,Args&&)::" << pThis);
        
        sys::sptr<CScene> pScene {new CScene};
        
// @todo: move to CSceneManager::load(pSceneLoader)
        CSceneManager::save(pScene);
        
// @todo: pScene = CSceneManager::load(tLoader);
        
        
      // @todo: loadScene ///////////////////////////////////////////////
        // for each element:node (root) in element:node.children
          // child = loadNode(element)
          // scene->root->nodes += child // & update scene->root->aabb
        
      // @todo: loadNode(element) ////////////////////////////////////////
        // parent = new CNode(type)
        // if type = scene // load unit
          // unit = loadUnit()
          // parent->unit = unit
              
          // for each element:node (root) in element:node.children
            // root = new CNode(root) // current root
            // for each element:node (joint|node|scene) in element:root 
              // child = loadNode(element)
              // root->nodes += child // & update root->aabb
            // parent->nodes += root // & update parent->aabb
            
          // @todo: add/push to octree->root using parent->aabb
            

                        
            
              
              
        // if type = joint // link joint
          // parent->link = findJoint()
          
          // for each element:node (joint|basic|scene) in element:joint 
            // child = loadNode(element)
            // parent->nodes += child // & update parent->aabb
          
        // else (basic)
          // for each element:node (joint|basic|scene) in element:joint 
            // child = loadNode(element)
            // parent->nodes += child // & update parent->aabb
              
      // @todo: loadUnit() /////////////////////////////////////////////////
        // unit = new CUnit
        // for each element:entity in element:unit
          // entity = loadEntity()
          // unit->entities += enitity
          
      // @todo: loadEntity() //////////////////////////////////////////////
        // entity = new CEntity(model)
        // model = CModelLoader::load(element:model->file)
        // entity->model = model
        // entity->aabb = model->aabb
        // for each mesh in geometry
          // material = CMaterialManager::load(element:material->file)
            // for each channel in material
              // case DIFFUSE:
                // texture = CTextureManager::load(element:texture->file)
                // material->channels[DIFFUSE]->texture = texture
              // case AMBIENT:
                // ...
          // mesh->material = material
          
      
        
        
        
        
        
        return new IScene{pScene};
      }
  };
}

#endif //__cym_cscene_hpp__
