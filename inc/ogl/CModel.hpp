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
  class CModelLoader;  typedef sys::CPointer<CModelLoader>  PModelLoader;
  
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
      friend class CModelStream;
    protected:
      std::vector<PMesh> mMeshes;
    public:
      CModel();
      CModel(PModelStream);
      ~CModel();
    public:
      virtual void load(PModelStream) final;
  };
  
  class CModelStream : public sys::CStream {
      friend class CModel;
      friend class CModelManager;
    public:
      using sys::CStream::CStream;
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelLoader; 
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> {
    public:
      CModelManager();
      ~CModelManager();
    public:
      PModel find(const sys::CString& name);
      
      template <typename T> PModel load(const T& from, const sys::CString& name = "") {
        throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__);
      }
      
      PModel load(const glm::SRectangle& from, const sys::CString& name = "") {
        
      }
      
      PModel load(const sys::CFile& from, const sys::CString& name = "") {
        log::nfo << "ogl::CModelManager::load(T&,CString&)::" << this << log::end;

        PModelLoader    pLoader {CModelLoader<T>::instance()};
        PModelStream    pStream {pLoader->load(from)};
        PModel          pModel  {new CModel{pStream}};


        // @todo: create key/id from descriptor
        // @todo: try to find model in cache using that key
        // @todo: else load it
        // @todo: update cache

        return pModel;
      }
  };
}

#endif //__ogl_cmodel_hpp__
