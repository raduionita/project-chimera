#ifndef __ogl_cmodel_hpp__
#define __ogl_cmodel_hpp__

#include "sys/CPointer.hpp"
#include "sys/CSingleton.hpp"
#include "ogl/CResource.hpp"

namespace ogl {
  class CModel;        typedef sys::CPointer<CModel>        PModel; 
  class CModelManager; typedef sys::CPointer<CModelManager> PModelManager;
  class CModelLoader;  typedef sys::CPointer<CModelLoader>  PModelLoader; // data that describes the model
  
  class CModel : public ogl::CResource { };
  
  class CModelManager : public ogl::CResourceManager, public sys::CSingleton<CModelManager> { };
  
  class CModelLoader { };
}

#endif //__ogl_cmodel_hpp__
