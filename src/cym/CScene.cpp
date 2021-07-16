#include "cym/CScene.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  
  // node ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: replace std::map<name_t,CNode*> with std::map<id_t,CNode*> 
  uint CNode::sID {0};
  
  void CNode::push(sys::spt<CNode> tNode) {
    CYM_LOG_NFO("cym::CNode::push(sys::spt<CNode>)::" << this << tNode->getType());
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
  
  sys::spt<CNode> CNode::pull(const cym::name& tName) {
    CYM_LOG_NFO("cym::CNode::pull(cym::name&)::" << this);
    // get node from mNodes
    auto it = mNodes.find(tName);
    if (it != mNodes.end()) {
      sys::spt<CNode> tNode {it->second};
      // remove from mNodes
      mNodes.erase(it);
      //  shrink this AABB, and this.mRoot's AABB // rebuild this.mAABB from this.mNodes (children's) mAABB's      
      shrink();
      return tNode;
    }
    return nullptr;
  }
  
  void CNode::yield() {
    CYM_LOG_NFO("cym::CNode::yield()::" << this);
    if (mRoot) {
      // detach from parent/this.mRoot
      mRoot->mNodes.erase(mName);
      // shrink (mRoot) parent's AABB
      mRoot->shrink();
      // remove parent
      mRoot = nullptr;
    }
  }
  
  void CNode::cling(sys::spt<CNode> tParent) {
    CYM_LOG_NFO("cym::CNode::cling(sys::sptr<CNode>)::" << this);
    // attach to parent/this.mRoot
    tParent->push(this);
  }
  
  void CNode::shift(sys::spt<CNode> tParent) {
    CYM_LOG_NFO("cym::CNode::shift(sys::spt<CNode>)::" << this);
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
  
  void CNode::extend(const glm::aabb& tAABB) {
    CYM_LOG_NFO("cym::CNode::extend(glm::aabb&)::" << this);
    // recursively call extend() from this to parent (mRoot)
    mAABB.extend(tAABB);
    if (mRoot) {
      mRoot->extend(tAABB);
    }
  }
  
  bool CNode::shrink() {
    CYM_LOG_NFO("cym::CNode::shrink()::" << this);
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
  
  // tree ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CCell::CCell() : mDepth{0}, mRoot{nullptr}, mType{CCell::ROOT} {
    CYM_LOG_NFO("cym::CBranch::CBranch()::" << this);
  }
  
  CCell::CCell(sys::wpt<CCell> tRoot, const glm::aabb& tAABB, CCell::EType tType) : mDepth{tRoot->mDepth + 1}, mType{tType}, mAABB{tAABB}, mRoot{tRoot} {
    CYM_LOG_NFO("cym::CBranch::CBranch(sys::wpt<CBranch>,glm::aabb&,EType:"<<tType<<")::" << this);
  }
  
  CCell::CCell(sys::wpt<CCell> tRoot, CCell::EType tType) : mDepth{tRoot->mDepth + 1}, mType{tType}, mRoot{tRoot} {
    CYM_LOG_NFO("cym::CBranch::CBranch(sys::wpt<CBranch>,EType:"<<tType<<")::" << this);
    
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
  
  sys::vector<sys::spt<TNode<CNode::SCENE>>> CCell::cull() {
    CYM_LOG_NFO("cym::CBranch::cull()::" << this);
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
  
  void CCell::push(sys::spt<TNode<CNode::SCENE>> tNode, bool tForce/*=false*/) {
    
// @todo: if tNode.mTransform.isIdentity() // = 0 // => no aabb change
    
    // take node's transform into consideration // node's AABB after transform (absolute position)    
    const glm::aabb kAABB {tNode->mTransform * tNode->mAABB};
    
    // if node.aabb INSIDE this.aabb // push it down the cells until it sits on a leaf
    if (tForce || mAABB.compare(kAABB) == glm::ECompare::INSIDE) {
      CYM_LOG_NFO("cym::CBranch::push(sys::spt<TNode<CNode::SCENE>>," << tForce <<")::" << this << " INSIDE");
      // limit branching using kMaxDepth
      if (mDepth < kMaxDepth) {
            
// @todo: find a way to know in which cell tNode goes or it stays here // before compare(-ing) or creating cells

        // re-use this
        glm::aabb tAABB;
        // for each cell(type) in this.mBranches
        for (auto& tType : kTypes) {
          // DO NOT create useless cells // find a way to test agains (potential) child cells W/O creating them
          sys::spt<CCell>& tBranch = mCells[tType];
          const bool bBranch {tBranch != nullptr};
          if (bBranch) {
            tAABB = tBranch->mAABB;
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
          if (tAABB.compare(kAABB) == glm::ECompare::INSIDE) {
            // create only if it's inside
            if (!bBranch) {
              tBranch = new CCell{this, tAABB, tType};
            }
            // push to this child // the (true) here will prevent an extra compare
            tBranch->push(tNode,true);
            return;
          }
        }
      }
      // else (if not inside any child) add tNode to mNodes  this.mNodes += node
      mNodes.push_back(tNode);
      return;
    // else (OUTSIDE or INTERSECT) but NOT root => try to push to parent (go up, since parent needs expanding too)
    } else if (mRoot != nullptr) {
      CYM_LOG_NFO("cym::CBranch::push(sys::spt<TNode<CNode::SCENE>>)::" << this << " OUTSIDE|INTERSECT (non-root)");
      mRoot->push(tNode);
      return;
    // else (OUTSIDE or INTERSECT) // expand the tree // (here) mTrunk = nullptr
    } else {
      CYM_LOG_NFO("cym::CBranch::push(sys::spt<TNode<CNode::SCENE>>)::" << this << " OUTSIDE|INTERSECT (root)");
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
  
  sys::spt<CResult> CCell::find(const CQuery& tQuery) {
    // CYM_LOG_NFO("cym::CCell::find(CQuery&)::" << this);
    
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
  
  CScene::CScene(const cym::name& tName) : cym::CResource(tName), mNode{new TNode<CNode::BASIC>{"root"}}, mCell{new CCell} {
    CYM_LOG_NFO("cym::CScene::CScene(cym::name&)::" << this); 
  }
  
  CScene::CScene(sys::spt<CSceneLoader> pLoader) : mNode{new TNode<CNode::BASIC>{"root"}}, mCell{new CCell} {
    CYM_LOG_NFO("cym::CScene::CScene(sys::spt<CSceneLoader>)::" << this);
    load(pLoader);
  }
  
  CScene::~CScene() {
    CYM_LOG_NFO("cym::CScene::~CScene()::" << this << " NAME:" << mName);
  }
  
  void CScene::load(sys::sptr<CSceneLoader>) {
    CYM_LOG_NFO("cym::CScene::load(sys::sptr<CSceneLoader>)::" << this);

// @todo: remember mRoot already exists // DO NOT create another one
    
// @todo: load scene
  // create mTree
  // append stuff to mRoot


  }
  
  
  sys::spt<TNode<CNode::SCENE>> CScene::push(sys::sptr<IModel> tModel, const glm::xform& tXForm/*=0*/) {
    CYM_LOG_NFO("cym::CScene::push(sys::sptr<IModel>)::" << this);
    // name it
    const cym::name& tName {sys::string{"model@"} + tModel->getName()};
    
    // create a node:scene
    sys::sptr<TNode<ENode::SCENE>> tNodeScene {new TNode<ENode::SCENE>{tName,tXForm}};
    // create a node:model
    sys::sptr<TNode<ENode::MODEL>> tNodeModel {new TNode<ENode::MODEL>{tName,tModel}};
    // attach node:model to node:scene
    tNodeScene->push(tNodeModel);
    
    // insert node:scene at CScene:node (xml's start/root node) 
    mNode->push(tNodeScene);
    // insert node:scene in CScene:cell (scene's octree-like structure),
    mCell->push(tNodeScene);
  
// @todo: use hints to tell where to insert

    return tNodeScene;
  }

  sys::spt<CResult> CScene::find(const CQuery& tQuery) {
    // CYM_LOG_NFO("cym::CScene::find(CQuery&)::" << this);
    
    // forward the query to the root cell to run it recursivelly down the cells
    mCell->find(tQuery);
    
// @todo: order the results using CQuery::mOrder
    
    return tQuery.mResult;
  }
  
  
  
  // managers ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CSceneManager::CSceneManager()  { 
    CYM_LOG_NFO("cym::CSceneManager::CSceneManager()::" << this); 
  }
  
  CSceneManager::~CSceneManager() { 
    CYM_LOG_NFO("cym::CSceneManager::~CSceneManager()::" << this);
    //for (auto it = mScenes.begin(); it != mScenes.end(); )
      //CSceneManager::kill(it->second);
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TSceneLoader<sys::CFile>::load(sys::sptr<CResourceLoader> pResourceLoader) {
    CYM_LOG_NFO("cym::TSceneLoader<sys::CFile>::load(sys::sptr<CResourceLoader>)::" << this);
    
    auto pCodec = cym::CCodecManager::getCodec(mFile.ext());
    
// @todo: this gets deleted after returns from ->decode(sys::sptr<CModelLoader>)
    
    pCodec->decode(pResourceLoader);
  }
}
