#include "cym/CScene.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  
  // node ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: replace std::map<name_t,CNode*> with std::map<id_t,CNode*> 
  uint CNode::sID {0};
  
  CNode::CNode(const sys::string& tName, const glm::aabb& tAABB/*=0*/, const glm::xform& tForm/*=0*/) : mName{tName}, mAABB{tAABB}, mTransform{tForm}, mPosition{mTransform.position}, mOrientation{mTransform.orientation}, mScale{mTransform.scale} { 
    SYS_LOG_NFO("cym::CNode::CNode(sys::string&,glm::aabb& glm::xform&)::" << this/* << " NAME:" << mName*/);
// @todo: add CAGE to mSymbols  
  }
  
  CNode::~CNode() { 
    SYS_LOG_NFO("cym::CNode::~CNode()::" << this/* << " NAME:" << mName*/); 
  }
  
  void CNode::push(sys::spo<CNode> tNode) {
    SYS_LOG_NFO("cym::CNode::push(sys::spo<TNode<"<< tNode->getType() <<">>)::" << this/* << " E:" << getType()*/);
    // prevend double insert 
    auto it = mNodes.find(tNode->mName);
    
// @todo: maybe (if found) do a merge or update/overwrite
    
    if (it != mNodes.end())
      return;
    // attach to root
    tNode->mRoot = this;
    // add to this's children
    mNodes.insert(std::pair{tNode->mName, tNode});
    // expand this AABB, expand this.mRoot AABB...and so on
    extend(tNode->mAABB);
  }
  
  sys::spo<CNode> CNode::pull(const sys::string& tName) {
    SYS_LOG_NFO("cym::CNode::pull(sys::string&)::" << this);
    // get node from mNodes
    auto it = mNodes.find(tName);
    if (it != mNodes.end()) {
      sys::spo<CNode> tNode {it->second};
      // remove from mNodes
      mNodes.erase(it);
      //  shrink this AABB, and this.mRoot's AABB // rebuild this.mAABB from this.mNodes (children's) mAABB's      
      shrink();
      return tNode;
    }
    return nullptr;
  }
  
  void CNode::yield() {
    SYS_LOG_NFO("cym::CNode::yield()::" << this);
    if (mRoot) {
      // detach from parent/this.mRoot
      mRoot->mNodes.erase(mName);
      // shrink (mRoot) parent's AABB
      mRoot->shrink();
      // remove parent
      mRoot = nullptr;
    }
  }
  
  void CNode::cling(sys::spo<CNode> tParent) {
    SYS_LOG_NFO("cym::CNode::cling(sys::spo<CNode>)::" << this);
    // attach to parent/this.mRoot
    tParent->push(this);
  }
  
  void CNode::shift(sys::spo<CNode> tParent) {
    SYS_LOG_NFO("cym::CNode::shift(sys::spo<CNode>)::" << this);
    // yield + cling | combined // = move from one parent to another
    // yield
    if (mRoot) {
      // detach from parent/this.mRoot
      mRoot->mNodes.erase(mName);
      // shrink (mRoot) parent's AABB
      mRoot->shrink();
      // remove parent
      mRoot = nullptr;
    }
    // cling
    tParent->push(this);
  }
  
  void CNode::extend(const glm::aabb& tAABB)  {
    SYS_LOG_NFO("cym::CNode::extend(glm::aabb&)::" << this/* << " E:" << getType()*/);
    // recursively call extend() from this to parent (mRoot)
    mAABB.extend(tAABB);
    if (mRoot) {
      mRoot->extend(tAABB);
    }
  }
  
  bool CNode::shrink() {
    SYS_LOG_NFO("cym::CNode::shrink()::" << this);
    // shrink this.mAABB by tAABB, rebuild this.mAABB from its children (mNodes)
    glm::aabb tAABB {mAABB};
    mAABB = 0.f;
    for (auto const& [tName,tNode] : mNodes)
      mAABB.extend(tNode->mAABB);
    // root, only if there was a change
    bool tShrunk = tAABB != mAABB; 
    if (tShrunk && mRoot)
      mRoot->shrink();
    // there was a change
    return tShrunk;
  }
  
  // node::entity ////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // node::model /////////////////////////////////////////////////////////////////////////////////////////////////////
  
  TNode<ENode::MODEL>::TNode(sys::spo<CGeometry> pGeometry) : TNode<ENode::DRAWABLE>(sys::string{"model@"}+pGeometry->getName(), pGeometry->getAABB()), mGeometry{pGeometry} { 
    SYS_LOG_NFO("cym::TNode<ENode::MODEL>::TNode(sys::spo<CGeometry>)::" << this/* << " NAME:" << pGeometry->getName()*/);
  }
  
  TNode<ENode::MODEL>::TNode(const sys::string& tName, sys::spo<CGeometry> pGeometry) : TNode<ENode::DRAWABLE>(tName, pGeometry->getAABB()), mGeometry{pGeometry} { 
    SYS_LOG_NFO("cym::TNode<ENode::MODEL>::TNode(sys::string&,sys::spo<CGeometry>)::" << this/* << " NAME:" << mName*/);
  }
  
  // node::camera ////////////////////////////////////////////////////////////////////////////////////////////////////
  
  TNode<ENode::CAMERA>::TNode(EScope tScope/*=EScope::GAME*/) : TNode<ENode::BASIC>(sys::string("camera@")+sys::to_string(tScope)), mScope{tScope} {
    SYS_LOG_NFO("cym::TNode<ENode::CAMERA>::TNode(EScope)::" << this/* << " NAME:" << mName*/);
  }
  
  TNode<ENode::CAMERA>::TNode(const glm::vec3& tTarget, const glm::real tFOV/*=90.f*/, const glm::real tRatio/*=1.333f*/, const glm::real tNear/*=0.1f*/, const glm::real tFar/*=100.f*/, EScope tScope/*=EScope::GAME*/) : TNode<ENode::BASIC>(sys::string("camera")+sys::to_string(tScope)), mTarget{tTarget}, mScope{tScope}, mFOV{tFOV}, mRatio{tRatio}, mNear{tNear}, mFar{tFar} { 
    SYS_LOG_NFO("cym::TNode<ENode::CAMERA>::TNode(glm::vec3&,glm::real,glm::real,glm::real,glm::real,EScope)::" << this/* << " NAME:" << mName*/);
  }
  
  TNode<ENode::CAMERA>::TNode(const glm::real tFOV/*=90.f*/, const glm::real tRatio/*=1.333f*/, const glm::real tNear/*=0.1f*/, const glm::real tFar/*=100.f*/, EScope tScope/*=EScope::GAME*/) : TNode<ENode::BASIC>(sys::string("camera")+sys::to_string(tScope)), mScope{tScope}, mFOV{tFOV}, mRatio{tRatio}, mNear{tNear}, mFar{tFar} { 
    SYS_LOG_NFO("cym::TNode<ENode::CAMERA>::TNode(glm::real,glm::real,glm::real,glm::real,EScope)::" << this/* << " NAME:" << mName*/);
  }
  
  // tree ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CCell::CCell() : mDepth{0}, mRoot{nullptr}, mType{CCell::ROOT} {
    SYS_LOG_NFO("cym::CCell::CCell()::" << this);
  }
  
  CCell::CCell(sys::wpo<CCell> tRoot, const glm::aabb& tAABB, CCell::EType tType) : mDepth{tRoot->mDepth + 1}, mType{tType}, mAABB{tAABB}, mRoot{tRoot} {
    SYS_LOG_NFO("cym::CCell::CCell(sys::wpo<CCell>,glm::aabb&,EType:"<<tType<<")::" << this);
  }
  
  CCell::CCell(sys::wpo<CCell> tRoot, CCell::EType tType) : mDepth{tRoot->mDepth + 1}, mType{tType}, mRoot{tRoot} {
    SYS_LOG_NFO("cym::CCell::CCell(sys::wpo<CCell>,EType:"<<tType<<")::" << this);
    
    glm::real hX {glm::abs(tRoot->mAABB.max.x - tRoot->mAABB.min.x) / 2};
    glm::real hY {glm::abs(tRoot->mAABB.max.y - tRoot->mAABB.min.y) / 2};
    glm::real hZ {glm::abs(tRoot->mAABB.max.z - tRoot->mAABB.min.z) / 2};
    
    bool tLeft {tType == 0 || tType == 2 || tType == 4 || tType == 6};
    bool tDown {tType == 0 || tType == 1 || tType == 4 || tType == 5};
    bool tBack {tType == 0 || tType == 1 || tType == 2 || tType == 3};
    
    mAABB.min.x = tRoot->mAABB.min.x + (tLeft ? 0.f : hX); 
    mAABB.min.y = tRoot->mAABB.min.y + (tDown ? 0.f : hY); 
    mAABB.min.z = tRoot->mAABB.min.z + (tBack ? 0.f : hZ);
    mAABB.max.x = tRoot->mAABB.max.x - (tLeft ? hX : 0.f); 
    mAABB.max.y = tRoot->mAABB.max.y - (tDown ? hY : 0.f); 
    mAABB.max.z = tRoot->mAABB.max.z - (tBack ? hZ : 0.f);
  }
  
  sys::vector<sys::spo<TNode<ENode::ENTITY>>> CCell::cull() {
    SYS_LOG_NFO("cym::CCell::cull()::" << this);
    // get ALL children elements
    decltype(mNodes) tNodes;
    const bool bEmpty {mNodes.empty()};
    // should the nodes from this be culled or just the children
    if (!bEmpty) {
      tNodes.insert(tNodes.end(), mNodes.begin(), mNodes.end());
    }
    // cull all children
    for (auto& tCell : mCells) if (tCell != nullptr) {
      decltype(mNodes) tCulled = tCell->cull();
      tNodes.insert(tNodes.end(), tCulled.begin(), tCulled.end());
      // destroy the child cell when done      
      mCells[tCell->mType] = nullptr;
    }
    // empty nodes
    if (!bEmpty) {
      mNodes.clear();
    }
    // return recursivelly
    return tNodes;
  }
  
  void CCell::push(sys::spo<TNode<ENode::ENTITY>> tNode, bool tForce/*=false*/) {
    
// @todo: if tNode.mTransform.isIdentity() // = 0 // => no aabb change
    
    // take node's transform into consideration // node's AABB after transform (absolute position)    
    const glm::aabb kAABB {tNode->getAABB()}; // (here) absolute aabb
    
    // if node.aabb INSIDE this.aabb // push it down the cells until it sits on a leaf
    if (tForce || glm::compare(mAABB,kAABB) == glm::ECompare::INSIDE) {
      
      // if node's AABB is point (has not volume) or is zero 
      if (kAABB.isPoint()) {
        SYS_LOG_NFO("cym::CCell::push(sys::spo<TNode<ENode::ENTITY>>," << tForce <<")::" << this << " INSIDE (point)");
        // do nothing (basically, insert it here)
        mNodes.push_back(tNode);
        return;
      // if limit branching using kMaxDepth
      } else if (mDepth < kMaxDepth) {
            
// @todo: find a way to know in which cell tNode goes or it stays here // before compare(-ing) or creating cells

        // re-use this
        glm::aabb tAABB;
        // for each cell(type) in this.mCells
        for (auto& tType : kTypes) {
          // DO NOT create useless cells // find a way to test agains (potential) child cells W/O creating them
          sys::spo<CCell>& tCell = mCells[tType];
          const bool bCell {tCell != nullptr};
          if (bCell) {
            tAABB = tCell->mAABB;
          } else {
            // type to cell
            const bool tLeft {tType == 0 || tType == 2 || tType == 4 || tType == 6};
            const bool tDown {tType == 0 || tType == 1 || tType == 4 || tType == 5};
            const bool tBack {tType == 0 || tType == 1 || tType == 2 || tType == 3};
            // half a distance
            const glm::real hX {(mAABB.max.x - mAABB.min.x) / 2};
            const glm::real hY {(mAABB.max.y - mAABB.min.y) / 2};
            const glm::real hZ {(mAABB.max.z - mAABB.min.z) / 2};
            // update new cell's AABB
            tAABB.min.x = mAABB.min.x + (tLeft ? 0.f : hX); 
            tAABB.min.y = mAABB.min.y + (tDown ? 0.f : hY); 
            tAABB.min.z = mAABB.min.z + (tBack ? 0.f : hZ);
            tAABB.max.x = mAABB.max.x - (tLeft ? hX : 0.f); 
            tAABB.max.y = mAABB.max.y - (tDown ? hY : 0.f); 
            tAABB.max.z = mAABB.max.z - (tBack ? hZ : 0.f);
          }
          // if node.aabb INSIDE cell.aabb
          if (glm::compare(tAABB,kAABB) == glm::ECompare::INSIDE) {
            SYS_LOG_NFO("cym::CCell::push(sys::spo<TNode<ENode::ENTITY>>," << tForce <<")::" << this << " INSIDE (child)");
            // create only if it's inside
            if (!bCell) {
              tCell = new CCell{this, tAABB, tType};
            }
            // push to this child // the (true) here will prevent an extra compare
            tCell->push(tNode, true);
            return;
          }
        }
        // else (if not inside any child) add tNode to mNodes  this.mNodes += node
        SYS_LOG_NFO("cym::CCell::push(sys::spo<TNode<ENode::ENTITY>>," << tForce <<")::" << this << " INSIDE (here)");
        mNodes.push_back(tNode);
        return;
      } else {
        // else (if not inside any child) add tNode to mNodes  this.mNodes += node
        SYS_LOG_NFO("cym::CCell::push(sys::spo<TNode<ENode::ENTITY>>," << tForce <<")::" << this << " INSIDE (direct)");
        mNodes.push_back(tNode);
        return;
      }
    // else (OUTSIDE or INTERSECT) but NOT root => try to push to parent (go up, since parent needs expanding too)
    } else if (mRoot != nullptr) {
      SYS_LOG_NFO("cym::CCell::push(sys::spo<TNode<ENode::ENTITY>>)::" << this << " OUTSIDE|INTERSECT (non-root)");
      mRoot->push(tNode);
      return;
    // else (OUTSIDE or INTERSECT) // expand the tree // (here) mTrunk = nullptr
    } else {
      SYS_LOG_NFO("cym::CCell::push(sys::spo<TNode<ENode::ENTITY>>)::" << this << " OUTSIDE|INTERSECT (root)");
      // get ALL children elements // tCulled will hold all CNode(s), including from this cell
      auto tCulled {cull()};
      // store node here
      tCulled.push_back(tNode);
      // expand this.aabb by adding node's (since node is outside)
      mAABB.extend(kAABB);
      
// @todo: distroy + create OR repurpose mBranches
      
      // for each tCulled => try to re-insert ->push(tCull)
      for (auto&& tCull : tCulled) {
        push(tCull,true);
      }
      return;
    }
  }
  
  sys::spo<CResult> CCell::find(const CQuery& tQuery) {
    // SYS_LOG_NFO("cym::CCell::find(CQuery&)::" << this);
    
    // add each note in this cell (if it matches condition)
    for (auto& tNode : mNodes) {
      tQuery.mResult->mNodes.push_back(tNode);
    }
    
    // recursivelly down mCells // adding children's nodes 
    for (auto& tCell : mCells) if (tCell) {
      tCell->find(tQuery);
    }

// @todo: if (tQuery.hasFrustum())
  // @todo: filter using CQuery::mFrustum

// @todo: filter using CQuery::mType

// @todo: order using CQuery::mOrder

    return tQuery.mResult;
  }
  
  // scene ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CScene::CScene(const sys::string& tName) : cym::CResource(tName), mNode{new TNode<ENode::BASIC>{"root"}}, mCell{new CCell} {
    SYS_LOG_NFO("cym::CScene::CScene(sys::string&)::" << this); 
  }
  
  CScene::CScene(sys::spo<CSceneLoader> pLoader) : mNode{new TNode<ENode::BASIC>{"root"}}, mCell{new CCell} {
    SYS_LOG_NFO("cym::CScene::CScene(sys::spo<CSceneLoader>)::" << this);
    load(pLoader);
  }
  
  CScene::~CScene() {
    SYS_LOG_NFO("cym::CScene::~CScene()::" << this << " NAME:" << mName);
  }
  
  void CScene::load(sys::spo<CSceneLoader>) {
    SYS_LOG_NFO("cym::CScene::load(sys::spo<CSceneLoader>)::" << this);

// @todo: remember mRoot already exists // DO NOT create another one
    
// @todo: load scene
  // create mTree
  // append stuff to mRoot


  }
  
  sys::spo<CResult> CScene::find(const CQuery& tQuery) {
    // SYS_LOG_NFO("cym::CScene::find(CQuery&)::" << this);
    
    // forward the query to the root cell to run it recursivelly down the cells
    mCell->find(tQuery);
    
// @todo: order the results using CQuery::mOrder
    
    return tQuery.mResult;
  }
  
  sys::spo<TNode<ENode::ENTITY>> CScene::push(sys::spo<CGeometry> pGeometry, const glm::xform& tXForm/*=0*/) {
    SYS_LOG_NFO("cym::CScene::push(sys::spo<CGeometry>)::" << this);
    // name it
    const sys::string& tName {sys::string{"model@"} + pGeometry->getName()};
    // create a node:entity
    sys::spo<TNode<ENode::ENTITY>> tEntity {new TNode<ENode::ENTITY>{tName, glm::ZERO, tXForm}};
    // create a node:model
    sys::spo<TNode<ENode::MODEL>>  tModel  {new TNode<ENode::MODEL>{tName,pGeometry}};
    // attach node:model to node:scene
    tEntity->push(tModel);
    // insert node:entity at CScene:node (xml's start/root node)
    mNode->push(tEntity);
    // insert node:entity in CScene:cell (scene's octree-like structure),
    mCell->push(tEntity);
    // return the entity
    return tEntity;
  }
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CSceneManager::CSceneManager()  { 
    SYS_LOG_NFO("cym::CSceneManager::CSceneManager()::" << this); 
  }
  
  CSceneManager::~CSceneManager() { 
    SYS_LOG_NFO("cym::CSceneManager::~CSceneManager()::" << this);
    //for (auto it = mScenes.begin(); it != mScenes.end(); )
      //CSceneManager::kill(it->second);
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TSceneLoader<sys::file>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TSceneLoader<sys::file>::load(sys::spo<CResourceLoader>)::" << this);
    
    auto pCodec = cym::CCodecManager::getCodec(mFile.ext());
    
// @todo: this gets deleted after returns from ->decode(sys::spo<CGeometryLoader>)
    
    pCodec->decode(pResourceLoader);
  }
  
  // logging /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CNode& node) {
    std::ostringstream oss;
    
    static uint tSpaces = 0;
    
    oss << "node:";
  
    switch (node.getType()) {
      case ENode::BASIC  : oss << "basic";  break;
      case ENode::JOINT  : oss << "joint";  break;
      case ENode::ENTITY : oss << "entity";  break;
      case ENode::MODEL  : oss << "model";  break;
      case ENode::LIGHT  : oss << "light";  break;
      case ENode::CAMERA : oss << "camera";  break;
      case ENode::FORCE  : oss << "force";  break;
      case ENode::EMITTER: oss << "emitter";  break;
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
  
  std::ostream& operator <<(std::ostream& out, const CNode& node) {
    static uint tSpaces = 0;
    
    out << "node:";
  
    switch (node.getType()) {
      case ENode::BASIC  : out << "basic";  break;
      case ENode::JOINT  : out << "joint";  break;
      case ENode::ENTITY : out << "entity";  break;
      case ENode::MODEL  : out << "model";  break;
      case ENode::LIGHT  : out << "light";  break;
      case ENode::CAMERA : out << "camera";  break;
      case ENode::FORCE  : out << "force";  break;
      case ENode::EMITTER: out << "emitter";  break;
      default: out << (uint)(node.getType()); break;
    }
    
    out << '@' << node.getName() << '#' << node.mAABB << 'n' << node.mNodes.size();
    
    for (auto it = node.mNodes.begin(); it != node.mNodes.end(); ++it) {
      out << '\n' << std::string(tSpaces++, ' ') << 'L' << *(it->second);
      tSpaces--;
    }
    
    return out;
  }
  
  const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CCell& cell) {
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
  
  std::ostream& operator <<(std::ostream& out, const CCell& cell) {
    static uint tSpaces = 0;
    
    out << "cell@" << cell.mType << 'd' << cell.mDepth << '#' << cell.mAABB << 'n' << cell.mNodes.size(); 
    
    for (auto& tCell : cell.mCells) if (tCell) {
      out << '\n' << std::string(tSpaces++, ' ') << 'L' << *(tCell);
      tSpaces--;
    }
    
    return out;
  }
  
  const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CScene& scene) {
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
  
  std::ostream& operator <<(std::ostream& out, const CScene& scene) {
    out << "scene:" << '\n';
    out << ".node:" << '\n';
    out << *(scene.mNode);
    out << '\n';
    out << ".cell:" << '\n';
    out << *(scene.mCell);
    return out;
  }
}
