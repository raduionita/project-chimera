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
  
  class CModelStream : public sys::CStream {
      friend class CModel;
      friend class CModelManager;
    public:
      using sys::CStream::CStream;
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> class CModelLoader : ogl::CResourceLoader {
      friend class CModel;
      friend class CModelManager;
    public:
      virtual PModel load(const T&) = 0;
    protected:
  };
  
  class CFileModelLoader : CModelLoader<sys::CFile> {
      virtual PModel load(const sys::CFile& file) override;
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> {
    public:
      CModelManager();
      ~CModelManager();
    public:
      PModel find(const sys::CString& name);
      
      template <typename T> PModel load(const T& from, const sys::CString& name = "") {
        PModel       pModel;
        PModelStream pStream;
        
        PModelLoader<T> pLoader = loader(from);
        if (pLoader) {
          
        }
        
        return pModel;
      }
      
      PModel load(const glm::SRectangle& from, const sys::CString& name = "") {
        
      }
      
      PModel load(const sys::CFile& from, const sys::CString& name = "") {
        log::nfo << "ogl::CModelManager::load(T&,CString&)::" << this << log::end;

        PModelLoader    pLoader ; // @todo: produce it somehow
        PModel          pModel  {new CModel{pLoader}};


        // @todo: create key/id from descriptor
        // @todo: try to find model in cache using that key
        // @todo: else load it
        // @todo: update cache

        return pModel;
      }
  };
}

#endif //__ogl_cmodel_hpp__
