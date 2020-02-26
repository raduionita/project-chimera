#ifndef __ogl_cmodel_hpp__
#define __ogl_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "ogl/CResource.hpp"
#include "ogl/CMaterial.hpp"

#include <tuple>

namespace ogl {
  class CModel;        typedef sys::CPointer<CModel>        PModel; 
  class CMesh;         typedef sys::CPointer<CMesh>         PMesh; 
  class CModelManager; typedef sys::CPointer<CModelManager> PModelManager;
  class CModelStream;  typedef sys::CPointer<CModelStream>  PModelStream;
  template <typename T> class CModelLoader; template <typename T> using PModelLoader =  sys::CPointer<CModelLoader<T>>;
  
  // model ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CMesh {
      friend class CModel;
    protected:
      PMaterial mMaterial;
      PModel    mParent;
  };
  
  class CModel : public ogl::CResource {
      friend class CMesh;
      friend class CModelManager;
    protected:
      std::vector<PMesh> mMeshes;
    public:
      CModel();
      CModel(PModelStream);
      ~CModel();
    public:
      virtual void load(PModelStream) final;
  };
  
  // stream //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelStream : public ogl::CResourceStream {
      friend class CModel;
      friend class CModelManager;
    public:
      using ogl::CResourceStream::CResourceStream;
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> class CModelLoader : public ogl::CResourceLoader {
      friend class CModel;
      friend class CModelManager;
    public:
      virtual PModelStream load(const T&) = 0;
    protected:
  };
  
  class CFileModelLoader : public CModelLoader<sys::CFile> {
    public:
      virtual PModelStream      load(const sys::CFile& file) override;
      static inline const char* name() { return typeid(CModelLoader<sys::CFile>).name(); }
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> {
    protected:
      std::map<sys::CString,ogl::PModel> mModels;
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
      
      template <typename T> PModel load(const sys::CString& name, const T& from) {
        log::nfo << "ogl::CModelManager::load(CString&,T&)::" << this << log::end;
        PModel       pModel;
        // try to find model in cache using that key
        auto it = mModels.find(name);
        if (it != mModels.end()) {
          pModel = it->second;
        } else {
          PModelStream           pStream;
          static PModelLoader<T> pLoader = sys::static_pointer_cast<PModelLoader<T>>(loader(typeid(CModelLoader<T>).name()));
          // is the loader ok?
          if (pLoader) {
            // @todo: start on another thread
            pStream = pLoader->load(from);
            // @todo: queue `new CModel{pStream}` for the main thread 
            pModel  = new CModel{pStream};
            // update cache
            mModels.insert({name,pModel});
          }
        }
        // return model;
        return pModel;
      }
  };
}

#endif //__ogl_cmodel_hpp__
