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
  class CResourceStream;  typedef sys::CPointer<CResourceStream>  PResourceStream;
  
  class CResource { // loadable entity/file/object
      friend class CResourceStream;
      friend class CResourceManager;
    public:
      CResource() = default;
      virtual ~CResource() = default;
  };
  
  class CResourceStream {
      friend class CResource;
      friend class CResourceManager;
    public:
      CResourceStream() = default;
      virtual ~CResourceStream() = default;
  };
  
  class CResourceManager {
      friend class CResource;
      friend class CResourceStream;
    public:
      CResourceManager() = default;
      virtual ~CResourceManager() = default;
    public:
  };
}

#endif //__ogl_cresource_hpp__
