#ifndef __cym_cmodel_hpp__
#define __cym_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/CThreader.hpp"
#include "sys/CBlock.hpp"
#include "cym/cym.hpp"
#include "cym/CResource.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CSkeleton.hpp"
#include "cym/CCollider.hpp"
#include "cym/CVertexArray.hpp"
#include "cym/CDataBuffer.hpp"
#include "cym/CVertexLayout.hpp"
#include "cym/CDrawable.hpp"
#include "cym/CInstance.hpp"
#include "glm/CAABB.hpp"
#include "glm/CFrustum.hpp"

namespace cym {
  class CModel; class IModel; 
  class CMesh;  class IMesh;
  
  class CModelLoader; template<typename T> class TModelLoader;
  class CMeshLoader;  template<typename T> class TMeshLoader;
  
  class CModelManager;
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMesh : public cym::CResource, public cym::CDrawable {
      friend class IMesh;
      friend class CModel;
      friend class CMeshLoader;
      friend class CMeshManager;
      friend class CModelLoader;
      friend class CModelManager;
    public:
      typedef sys::sptr<CMesh> ptr_type;
      typedef cym::name        name_type;
    protected:
      CBufferRange         mRange;
      sys::wptr<CModel>    mModel;
      sys::sptr<CMaterial> mMaterial;
    public:
      CMesh(const std::string& tName) : cym::CResource(tName) { }
      CMesh(sys::sptr<CModel> pModel) : mModel{pModel} { }
      ~CMesh();
    public:
      inline void setMaterial(decltype(mMaterial) m) { mMaterial = m; }
      inline void setRange(const CBufferRange& r) { mRange = r; }
      // drawable
      virtual void draw() override;
  };
  
  class CModel : public cym::CResource, public cym::CDrawable {
      friend class IModel;
      friend class CMesh;
      friend class CModelManager;
    public:
      enum EFlag {
        FLAG       = 1, // 1 << 0
        POSITIONS  = FLAG << 1,
        TEXCOORDS  = FLAG << 2,
        NORMALS    = FLAG << 3,
        TANGENTS   = FLAG << 4,
        BINORMALS  = FLAG << 5,
        VERTICES   = POSITIONS | TEXCOORDS | NORMALS | TANGENTS | BINORMALS,
        MATERIALS  = FLAG << 7,
        TEXTURES   = FLAG << 8,
        SKELETON   = FLAG << 9,
        ANIMATIONS = FLAG << 10 | SKELETON,
        
        DEFAULT    = FLAG | VERTICES | MATERIALS | TEXTURES | ANIMATIONS,
        
        NORMALIZED = FLAG << 11,             // normalize position vectors | must have position
        INVERTED   = FLAG << 12 | NORMALS ,  // invert normals | must have normals
        REPEATUV   = FLAG << 13,             
        FLATFACE   = FLAG << 14,             // flat face - for loaded meshes this will used default normals - otherwise compute face normals
        
        FLIPXY     = FLAG << 15,
        FLIPYZ     = FLAG << 16,
        FLIPXZ     = FLAG << 17,
      };
    private:
      sys::sptr<CVertexArray>           mVAO;
      sys::sptr<CVertexBuffer>          mVBO;
      sys::sptr<CIndexBuffer>           mIBO;
      sys::sptr<CVertexLayout>          mVLO;
    protected:
// @todo: rename CGeometry to CData, & wrap mMeshes + mVAO... inside wapper class CGeometry 
      std::map<CMesh::name_type,sys::sptr<CMesh>> mMeshes;
      glm::aabb                                   mAABB;
// @todo: move collider at scene(node) level, as a component/plugin (for physics)?!
      cym::CCollider                              mCollider;
      sys::sptr<CSkeleton>                        mSkeleton {new CSkeleton};
// @todo: mGeometry // wrap meshes + vertex data inside a CGeometry, requires to rename the current CGeometry
// @todo: mAnimator // animations list wrapper // this should be common among other similar (skeleton) models
    public: // ctors
      using cym::CResource::CResource;
    public: // ctors
      CModel(const cym::name& tName = "");
      CModel(sys::spt<CModelLoader>);
      ~CModel();
    public: // operators
      inline sys::sptr<CMesh>& operator [](uint i)             { return getMesh(i); }
      inline sys::sptr<CMesh>& operator [](const cym::name& n) { return getMesh(n); }
    public: // get/setters
      inline  void addMesh(sys::sptr<CMesh> pMesh) { mMeshes.insert(std::pair(pMesh->mName, pMesh)); }
      inline sys::sptr<CMesh>& getMesh(const cym::name& name) { return mMeshes[name]; }
      inline sys::sptr<CMesh>& getMesh(uint i) { assert(i < mMeshes.size()); for (auto it = mMeshes.begin(); it != mMeshes.end(); ++it, i--) if (i == 0) return it->second; throw sys::exception("OUT OF BOUNDS",__FILE__,__LINE__); }
    public: // actions
      virtual void load(sys::sptr<CModelLoader>) final;
      virtual void draw() override;
  };

  // instances ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class IMesh : public cym::TInstance<CMesh> {
      friend class CMesh;
    protected:
      sys::sptr<IMaterial> mMaterial;
    public:
      using cym::TInstance<CMesh>::TInstance;
    public:
      inline CMesh&                getMesh() const { return mInstance.raw(); }
      inline sys::sptr<IMaterial>& getMaterial(const cym::name& tName) { if (!mMaterial) mMaterial = new IMaterial{mInstance->mMaterial}; return mMaterial; }
    public:
      inline void draw() { mInstance->draw(); }  
  };
  
  class IModel : public cym::TInstance<CModel> {
      friend class CModel;
      friend class CInstanceRegistry;
    protected:
      sys::CMap<cym::name, sys::sptr<IMesh>> mMeshes;
    public:
      using cym::TInstance<CModel>::TInstance;
    public:
      inline CModel&           getModel() const { return mInstance.raw(); }
      inline sys::sptr<IMesh>& getMesh(const cym::name& tName) { auto& pMesh = mMeshes[tName]; if (!pMesh) pMesh = new IMesh{mInstance->getMesh(tName)}; return pMesh; }
      inline sys::sptr<IMesh>& getMesh(uint i) { 
        for (auto it = mMeshes.begin(); it != mMeshes.end(); ++it)
          return it->second;
        auto& pMesh = mInstance->getMesh(i);
        return mMeshes.insert(std::pair(pMesh->getName(), pMesh)).first->second;
      }
      inline const cym::name&  getName() { return mInstance->getName(); }
      inline const glm::aabb&  getAABB() { return mInstance->mAABB; }
    public:
      inline void draw() { mInstance->draw(); }  
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMeshLoader : public CResourceLoader {
      friend class CMesh;
      friend class CModel;
      friend class CMeshManager;
      friend class CModelLoader;
      friend class CModelManager;
      typedef struct { uint nStart, nEnd; } range_type;
    protected:
      sys::sptr<cym::CMaterialLoader> mMaterialLoader;
      range_type                          mRange;
    public:
      using cym::CResourceLoader::CResourceLoader;
    public:
      virtual void load() {
        CYM_LOG_NFO("cym::CMeshLoader::load()::" << this);
      }
    public:
      inline sys::sptr<cym::CMaterialLoader>& getMaterialLoader() { if (!mMaterialLoader) mMaterialLoader = new CMaterialLoader; return mMaterialLoader; }
      inline sys::sptr<cym::CMaterialLoader>& useMaterialLoader(const std::string& tName) { if (!mMaterialLoader) mMaterialLoader = new CMaterialLoader{tName}; else mMaterialLoader->getName() = tName; return mMaterialLoader; }
      inline void                             setMaterialLoader(sys::sptr<CMaterialLoader> pLoader) { mMaterialLoader = pLoader; }
      inline range_type&                      getRange() { return mRange; }
  };
  
  class CModelLoader : public CResourceLoader {
      friend class CModel;
      friend class CModelManager;
      typedef std::map<std::string, sys::sptr<CMeshLoader>> mesh_map;
    public:
      using EFlag = CModel::EFlag;
    protected:
      uint                                          mFlags {0};
      cym::CGeometry                                mGeometry;
      std::map<std::string, sys::sptr<CMeshLoader>> mMeshLoaders;
    public:
      using CResourceLoader::CResourceLoader;
      inline CModelLoader(const cym::name& tName, uint eFlags = EFlag::DEFAULT) : CResourceLoader(tName), mFlags{eFlags} { CYM_LOG_NFO("cym::CModelLoader::CModelLoader(cym::name&,ushort)::" << this);  }
      inline ~CModelLoader() { CYM_LOG_NFO("cym::CModelLoader::~CModelLoader()::" << this); }
    public:
      virtual inline void load(sys::sptr<CResourceLoader>) { throw sys::exception("CModelLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      inline uint                    getFlags()                              { return mFlags; }
      inline bool                    hasFlag(EFlag e)                        { return mFlags & e; }
      inline bool                    hasFlags(uint es)                       { return mFlags & es; }
      inline cym::CGeometry&         getGeometry()                           { return mGeometry; }
      inline mesh_map&               getMeshLoaders()                        { return mMeshLoaders; }
      inline sys::sptr<CMeshLoader>& getMeshLoader(const std::string& tName) { auto& pLoader = mMeshLoaders[tName]; if (!pLoader) pLoader = new CMeshLoader{tName}; return pLoader; }
    public:
      template<typename T> inline static sys::sptr<TModelLoader<T>> from(const T& tSource) { return new TModelLoader<T>{tSource}; }
      template<typename T, typename... Args> inline static cym::name name(const T& tSource, Args&&... args) { return TModelLoader<T>::name(tSource, std::forward<Args>(args)...); }
    public:
      inline decltype(cym::CGeometry::mStream)& getStream() { return mGeometry.mStream; }
      inline decltype(cym::CGeometry::mLayout)& getLayout() { return mGeometry.mLayout; }
  };
  
  template<typename T> class TModelLoader : public CModelLoader { };
  
  template<> class TModelLoader<sys::CFile> : public CModelLoader {
      friend class CModelCodec;
    protected:
      sys::CFile mFile;
    public:
      inline TModelLoader(const sys::CFile& tFile, uint eFlags = EFlag::DEFAULT) : CModelLoader(tFile.path(), eFlags), mFile{tFile} { };
    public:
      inline static cym::name name(const sys::CFile& tFile) { return tFile.path(); }
      virtual void load(sys::sptr<CResourceLoader>) override;
    public:
      inline sys::CFile& getFile() { return mFile; }
  };
  
  template<> class TModelLoader<glm::SCube> : public CModelLoader {
    protected:
      glm::SCube mCube;
      uint       mXDivisions {1u};
      uint       mYDivisions {1u};
      uint       mZDivisions {1u};
    public:
      inline TModelLoader(const glm::SCube& tCube, uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tCube, 1u, 1u, 1u), eFlags), mCube(tCube) { }
      inline TModelLoader(const glm::SCube& tCube, uint nD, uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tCube, nD, nD, nD), eFlags), mCube{tCube}, mXDivisions{nD}, mYDivisions{nD}, mZDivisions{nD} { }
      inline TModelLoader(const glm::SCube& tCube, uint nXD, uint nYD, uint nZD, uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tCube, nXD, nYD, nZD), eFlags), mCube{tCube}, mXDivisions{nXD}, mYDivisions{nYD}, mZDivisions{nZD} { }
    public:
      inline static cym::name name(const glm::SCube& tCube, uint nXD = 1u, uint nYD = 1u, uint nZD = 1u) { return std::string("cube:")+sys::to_string(tCube.length,3)+"|"+std::to_string(nXD)+"x"+std::to_string(nYD)+"x"+std::to_string(nZD); }
      virtual void load(sys::sptr<CResourceLoader>) override;
    public:
      inline glm::SCube& getCube() { return mCube; }
  };
  
  template<> class TModelLoader<glm::rect> : public CModelLoader {
    protected:
      glm::rect mRectangle;
      uint      mDivisions  {1u};
      glm::vec3 mUp         {glm::Y}; // @todo
    public:
      inline TModelLoader(const glm::rect& tRect, uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tRect, 1u, glm::Y), eFlags), mRectangle(tRect) { }
      inline TModelLoader(const glm::rect& tRect, uint nDivisions, const glm::vec3& vUp, uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tRect, nDivisions, vUp), eFlags), mRectangle{tRect}, mDivisions{nDivisions}, mUp{vUp} { }
    public:
      inline static cym::name name(const glm::rect& tRect, uint nDivisions = 1u, const glm::vec3& vAxis = glm::Y) { return std::string("rect:") + sys::to_string(tRect.width, 3) + 'x' + sys::to_string(tRect.height, 3) + '|' + std::to_string(nDivisions) + '|' + sys::to_string(vAxis, 1); }
      virtual void load(sys::sptr<CResourceLoader>) override;
    public:
      inline glm::rect& geRectangle() { return mRectangle; }
  };
  
  template<> class TModelLoader<glm::frustum> : public CModelLoader {
    protected:
      glm::frustum mFrustum; // use planes normal as the up vector
      glm::uint    mDivisions {1u};
    public:
      inline TModelLoader(const glm::frustum& tFrustum, cym::uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tFrustum, 1u), eFlags), mFrustum{tFrustum} { }
      inline TModelLoader(const glm::frustum& tFrustum, const uint nDivisions, const uint eFlags = EFlag::DEFAULT) : CModelLoader(name(tFrustum,nDivisions),eFlags), mFrustum{tFrustum}, mDivisions{nDivisions} { }
    public:
      inline static cym::name name(const glm::frustum& f, const glm::uint d) { return std::string("frustum:") +'|'+ sys::to_string(d); }
      virtual void load(sys::sptr<CResourceLoader>) override;
    public:
      inline glm::frustum& getFrustum() { return mFrustum; }
  };
  
// @todo: pModelLoader->load(pModelLoader) there MUST be a better way, init() or exec() or run()  
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: CAnimatorManager
// @todo: CAnimationManager
  
  class CModelManager : public cym::TManager<CModel>, public sys::TSingleton<CModelManager> {
      friend class CModel;
      friend class CModelLoader;
    public:
      using EFlag = CModel::EFlag;
    protected:
      std::map<cym::name, sys::sptr<CModel>> mModels;
    public:
      CModelManager();
      ~CModelManager();
    public:
      static sys::sptr<CModel> pull(const cym::name& tName) {
        static auto self {cym::CModelManager::getSingleton()};
        CYM_LOG_NFO("cym::CModelManager::pull(cym::name&)::" << self);
        
        return self->mModels.extract(tName).mapped();
      }
      
      static bool kill(const cym::name& tName) {
        static auto self {cym::CModelManager::getSingleton()};
        CYM_LOG_NFO("cym::CModelManager::kill(cym::name&)::" << self);
        
        return self->mModels.size() < self->mModels.erase(tName);
      }
      
      static sys::sptr<CModel> find(const std::string& tName) {
        static auto pThis {cym::CModelManager::getSingleton()};
        auto it = pThis->mModels.find(tName);
        if (it != pThis->mModels.end()) {
          return it->second;
        }
        return nullptr;
      }
      
      static void save(sys::sptr<CModel> pModel) {
        static auto pThis {cym::CModelManager::getSingleton()};
        CYM_LOG_NFO("cym::CModelManager::save(sys::sptr<CModel>)::" << pThis);
        pThis->mModels.insert(std::pair(pModel->mName, pModel));
      }
      
      static sys::sptr<CModel> load(sys::sptr<CModelLoader> pModelLoader) {
        static auto self {cym::CModelManager::getSingleton()};
        CYM_LOG_NFO("cym::CModelManager::load(sys::sptr<CModelLoader>)::" << self);
        
        if (!pModelLoader) return nullptr;
        
        sys::sptr<CModel> pModel {new CModel{pModelLoader->getName()}};
        
        sys::async([pModel, pModelLoader](){
          
          pModelLoader->load(pModelLoader);
          
          for (auto&& [sMesh, pMeshLoader] : pModelLoader->mMeshLoaders) {
            
            sys::sptr<CMesh> pMesh {new CMesh{pMeshLoader->getName()}};
            
            // here u can make materials load ASYNC (decoupled from model loading) // model should render event w/o materials
            pMesh->mMaterial = cym::CMaterialManager::load(pMeshLoader->mMaterialLoader);
            pMesh->mRange    = {pMeshLoader->mRange.nStart, pMeshLoader->mRange.nEnd - pMeshLoader->mRange.nStart};
            pMesh->mModel    = pModel;
            
            pModel->addMesh(pMesh);
          }
          
          pModel->load(pModelLoader);
          
        }, sys::EAsync::SPAWN);
        
        CModelManager::save(pModel);
        
        return pModel;
      }
      
      template<typename T, typename... Args> static sys::sptr<IModel> load(const T& tSource, Args&&... args) {
        static auto pThis {cym::CModelManager::getSingleton()};
        CYM_LOG_NFO("cym::CModelManager::load(T&,Args&&)::" << pThis);
        
        sys::sptr<CModel> pModel;
        
        const cym::name&  tName {CModelLoader::name(tSource)};
        
        if (!sys::find(tName, pThis->mModels, pModel)) {
          sys::sptr<CModelLoader> tLoader = new TModelLoader<T>{tSource, std::forward<Args>(args)...};
        
          pModel = CModelManager::load(tLoader);
        }
        
        return new IModel{pModel};
      }
      
      // template<typename T> static sys::sptr<IModel> load(const T& tSource/*, uint eOptions = EOption::DEFAULT*/) {
      //   static auto pThis {cym::CModelManager::getSingleton()};
      //   CYM_LOG_NFO("cym::CModelManager::load(T&)::" << pThis);
      //
      //   sys::sptr<CModel> pModel;
      //   const cym::name&  tName {CModelLoader::name(tSource)};
      //  
      //   if (!sys::find(tName, pThis->mModels, pModel)) {
      //     sys::sptr<CModelLoader> tLoader {new TModelLoader<T>(tSource, EOption::DEFAULT)};
      //    
      //     pModel = CModelManager::load(tLoader);
      //   }
      //  
      //   return new IModel{pModel};
      // }
  };
}

#endif //__cym_cmodel_hpp__
