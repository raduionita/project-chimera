#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"
#include "sys/CException.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>
#include <functional>
#include <any>

namespace ogl {
  class CResource;        typedef sys::CPointer<CResource>        PResource;
  class CResourceManager; typedef sys::CPointer<CResourceManager> PResourceManager;
  class CResourceLoader;  typedef sys::CPointer<CResourceLoader>  PResourceLoader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceLoader;
      friend class CResourceManager;
    public:
      CResource() = default;
      virtual ~CResource() = default;
  };
  
  class CResourceLoader {
      friend class CResource;
      friend class CResourceManager;
    public:
      CResourceLoader() = default;
      virtual ~CResourceLoader() = default;
  };
  
  class CResourceManager {
      friend class CResource;
      friend class CResourceLoader;
    public:
      CResourceManager() = default;
      virtual ~CResourceManager() = default;
    public:
      static PResource load(const sys::CFile& file) { return nullptr; } 
  };
}

#endif //__ogl_cresource_hpp__
