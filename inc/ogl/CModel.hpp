#ifndef __ogl_cmodel_hpp__
#define __ogl_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "ogl/CResource.hpp"

namespace ogl {
  class CModel;        typedef sys::CPointer<CModel>        PModel; 
  class CModelManager; typedef sys::CPointer<CModelManager> PModelManager;
  class CModelLoader;  typedef sys::CPointer<CModelLoader>  PModelLoader; // data that describes the model
  
  class CModel : public ogl::CResource {
    public:
      CModel();
      CModel(PModelLoader);
  };
  
  class CModelLoader { };
  
  class CSphereModelLoader : public CModelLoader {
      
  };
  
  class CObjModelLoader : public CModelLoader {
    public:
      struct SDescriptor { 
        CString file;
        SDescriptor(const CString& file) : file{file} { }
      };
  };
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> {
    public:
      CModelManager();
      ~CModelManager();
    public:
      PModel find(const sys::CString& name);
      
      template <typename T> PModel load(const T& desc, const sys::CString& name = "") {
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
