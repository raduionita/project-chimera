#ifndef __ogl_cmodel_hpp__
#define __ogl_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "ogl/CResource.hpp"
#include "ogl/CMesh.hpp"

namespace ogl {
  class CModel;        typedef sys::CPointer<CModel>        PModel; 
  class CMesh;         typedef sys::CPointer<CMesh>         PMesh; 
  class CModelManager; typedef sys::CPointer<CModelManager> PModelManager;
  class CModelStream;  typedef sys::CPointer<CModelStream>  PModelStream;
  class CModelLoader;  typedef sys::CPointer<CModelLoader>  PModelLoader; // data that describes the model
  
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
      friend class CModelLoader;
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
    public:
  };
  
  // descriptors /////////////////////////////////////////////////////////////////////////////////////////////////////
  
  struct SModelDescriptor { };
  
  struct SShapeModelDescriptor : public SModelDescriptor {
    template <glm::EShape S> SShapeModelDescriptor(const glm::CShape<S>& shape) { }
  };
  
  struct SFileModelDescriptor : public SModelDescriptor {
    SFileModelDescriptor(const CString& file) { }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class BModelLoader { };
  class CModelLoader : public BModelLoader { };
  class CShapeModelLoader : public CModelLoader { };
  class CFileModelLoader : public CModelLoader { };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> {
    public:
      CModelManager();
      ~CModelManager();
    public:
      PModel find(const sys::CString& name);
      
      template <typename T, class = typename std::enable_if<std::is_convertible<T*,SModelDescriptor*>::value>::type> PModel load(const T& desc, const sys::CString& name = "") {
        // @todo: register all loaders through descriptors
        
        // 
        
        // @todo: create key/id from descriptor
        // @todo: try to find model in cache using that key
        // @todo: else load it
        // @todo: update cache
      }
  };
}

#endif //__ogl_cmodel_hpp__
