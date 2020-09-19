#ifndef __cym_cmodel_hpp__
#define __cym_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/CBlock.hpp"
#include "cym/CResource.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CVertexArray.hpp"
#include "cym/CBuffer.hpp"
#include "cym/CNode.hpp"

namespace cym {
  class CModel;        typedef sys::TPointer<CModel> PModel; 
  class CMesh;         typedef sys::TPointer<CMesh> PMesh; 
  class CModelManager; typedef sys::TPointer<CModelManager> PModelManager;
  class CMeshData;     typedef sys::TPointer<CMeshData> PMeshData;
  template<typename T> class TModelLoader; template<typename T> using PModelLoader = sys::TPointer<TModelLoader<T>>;
  class CModelInfo;
  template<typename T> class TModelInfo;
  
  // model ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMesh {
      friend class CModel;
    protected:
      PMaterial    mMaterial;
      sys::CString mName;
  };
  
  class CModel : public cym::CResource {
      friend class CMesh;
      friend class CModelManager;
    protected:
      cym::PVertexArray       mVAO;
      cym::PVertexBuffer      mVBO;
      cym::PIndexBuffer       mIBO;
      sys::CCollection<PMesh> mMeshes;
    public:
      CModel();
      CModel(CModelInfo&);
      ~CModel();
    protected:
      virtual void load(CModelInfo&) final;
  };
  
  class NMesh : public TNode<cym::CMesh> {
    protected:
    //cym::PMesh            mResource;
      cym::TNode<NMaterial> mMaterial;
  };
  
  class NModel : public TNode<cym::CModel> {
    protected:
    //cym::PModel             mResource;
      sys::CCollection<NMesh> mMeshes;
    public:
      NModel(cym::PModel m) : TNode(m) { throw sys::CException("NOT IMPLEMENTED!", __FILE__,__LINE__); }
  };
  
  // info ////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class CMeshInfo {
  // identifier
    sys::string   name;
  // fields
    cym::CMaterialInfo material;
  };
  
  class CModelInfo : public CResourceInfo {
    public:
      typedef sys::pair<sys::block<float>,sys::block<int>> data_type;
    public:
    // identifier/name
      sys::string                                   name;
    // data                                 
      sys::pair<sys::block<float>,sys::block<uint>> data;  // ::load({name, {vertices, indices}})
    // components
      sys::vector<CMeshInfo>                        meshes; 
    public:// ctors
      CModelInfo() {}
      CModelInfo(const sys::string& n) : name{n} {}
      CModelInfo(sys::string&& n) : name{n} {}
  };
  
  template<typename T> class TModelInfo : public CModelInfo {
      friend class CModel;
      friend class TModelLoader<T>;
    public: // fields
      T source;
    public: // ctors
      TModelInfo(const sys::string& n, const T& s) : CModelInfo(n), source{s} { }
      TModelInfo(const T& s) : CModelInfo(), source{s} { }
      TModelInfo(sys::string&& n, T&& s) : CModelInfo(std::move(n)), source{std::move(s)} { }
      TModelInfo(T&& s) : source{std::move(s)} { }
  };
  
  typedef TModelInfo<sys::CFile> CFileModelInfo;
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> class TModelLoader : public cym::CResourceLoader {
      friend class CModel;
      friend class CModelManager;
      friend class TModelInfo<T>;
    public:
      typedef TModelLoader<T> loader_type;
      typedef TModelInfo<T>   info_type;
    public:
      ~TModelLoader() { log::nfo << "cym::TModelLoader::~TModelLoader()::" << this << log::end; }
    public:
      virtual void load(cym::TModelInfo<T>&) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
  };
  
  class CFileModelLoader : public TModelLoader<sys::CFile> {
      friend class CModel;
      friend class CModelManager;
      friend class TModelInfo<sys::CFile>;
    protected:
      sys::CMap<sys::CString,PCodec> mCodecs;
    public:
      CFileModelLoader();
      ~CFileModelLoader();
    protected:
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CCodec*>::value>::type> inline void codec(T* pCodec) { mCodecs[pCodec->type()] = pCodec; }
      PCodec codec(const sys::CString& ext);
    public:
      virtual void              load(cym::CFileModelInfo&) override;
      static inline const char* type() { return typeid(TModelLoader<sys::CFile>).name(); }
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelManager : public cym::CResourceManager, public sys::TSingleton<CModelManager> {
      friend class CModel;
      friend class CModelData;
    protected:
      sys::CMap<sys::CString,cym::PModel> mModels;
    public:
      CModelManager();
      ~CModelManager();
    public:
      PModel find(const sys::CString& name) {
        auto it = mModels.find(name);
        if (it != mModels.end()) {
          return it->second;
        }
        return nullptr;
      }
      
      template<typename T> inline NModel load(const T& src) {
        log::nfo << "cym::CModelManager::load(T&)::" << this << log::end;
        return CModelManager::load<T>(TModelInfo<T>(src));
      }
      
      template<typename T> NModel load(const sys::CString& name, const T& from) {
        log::nfo << "cym::CModelManager::load(CString&,T&)::" << this << log::end;
        return CModelManager::load<T>(TModelInfo<T>{name,from});
        
        // // try to find model in cache using that key
        // auto it = mModels.find(name);
        // if (it != mModels.end()) {
        //   // return model
        //   return it->second;
        // } else {
        //   // static cache/remember loader
        //   static PModelLoader<T> pLoader = sys::static_pointer_cast<typename PModelLoader<T>::type>(loader(typeid(TModelLoader<T>).name()));
        //   // is the loader ok?
        //   if (pLoader) {
        //     // new model
        //     PModel pModel = new CModel;
        //    
        //     // @todo: <thread> on another thread
        //     pLoader->load(pModel,from);
        //     // @todo: </thread>
        //    
        //     // update cache
        //     mModels.insert({name,pModel});
        //     // return model
        //     return pModel;
        //   }
        //   // throw if now loader
        //   throw sys::CException("No loader found!",__FILE__,__LINE__);
        // }
      }
      
      template<typename T> NModel load(TModelInfo<T>&& info) {
        log::nfo << "cym::CModelManager::load(TModelInfo<T>&&)::" << this << log::end;
        
        PModel pModel;
        if (!sys::find(info.name,mModels,pModel)) {
          log::nfo << "cym::CModelManager::load(TModelInfo<T>&&)::" << this << "::not found" << log::end;
          // static cache/remember loader
          static const PModelLoader<T>& pLoader{sys::static_pointer_cast<typename PModelLoader<T>::type>(loader(typeid(TModelLoader<T>).name()))};
          // loader found?
            
          pLoader->load(info);
          log::nfo << "cym::CModelManager::load(TModelInfo<T>&&)::" << this << "::loader done" << log::end;
          
          pModel->load(info);
          log::nfo << "cym::CModelManager::load(TModelInfo<T>&&)::" << this << "::model done" << log::end;
          
        } else {
          log::nfo << "cym::CModelManager::load(TModelInfo<T>&&)::" << this << "::found" << log::end;
        }
        
        
        // ::load(CModel::SDescriptor) -> NNode<CModel>
          // find model
            // PModel pModel = CModelManager::mModels[zName]
            // NNode  oNode  = NNode<CModel>(pModel)                  // update NNode w/ CModel data (meshes)
          // make model
            // CModel::SDescriptor = CFileModelLoader::load(CFile);
            // ? = CShapeModelLoader::load(glm::shape);
            // ? = CDataModelLoader::load(data);
            // PModel pModel = new CModel(CModel::SDescriptor);
            // NNode  oNOde  = NNode<CModel>(pModel)                  // update NNode w/ CModel data (meshes)
          // apply stuff from CModel::SDescriptor FIELDS to oNode
            // meshes for each mesh
              // ::load(SMesh::SDescriptor)
                // 
          // return oNode;
        
        log::nfo << "cym::CModelManager::load(TModelInfo<T>&&)::" << this << "::done" << log::end;
        return pModel;
      }
  };
}

#endif //__cym_cmodel_hpp__
