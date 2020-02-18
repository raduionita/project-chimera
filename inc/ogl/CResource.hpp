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
  class CResourceLoader;  typedef sys::CPointer<CResourceLoader>  PResourceLoader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceStream;
      friend class CResourceManager;
      friend class CResourceLoader;
    public:
      CResource() = default;
      virtual ~CResource() = default;
  };
  
  class CResourceStream {
      friend class CResource;
      friend class CResourceManager;
      friend class CResourceLoader;
    public:
      CResourceStream() = default;
      virtual ~CResourceStream() = default;
  };
  
  class CResourceLoader {
      friend class CResource;
      friend class CResourceStream;
      friend class CResourceManager;
    public:
      CResourceLoader() = default;
      virtual ~CResourceLoader() = default;
    public:
      virtual const char* type() const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
  };
  
  class CResourceManager {
      friend class CResource;
      friend class CResourceStream;
      friend class CResourceLoader;
    protected:
      sys::CMap<sys::CString, PResourceLoader> mLoaders;
    public:
      CResourceManager() = default;
      virtual ~CResourceManager() = default;
    public:
      inline PResourceLoader loader(const char* ext) { auto it = mLoaders.find(ext); return it != mLoaders.end() ? it->second : nullptr; }
      inline void            loader(PResourceLoader pLoader) { mLoaders[pLoader->type()] = pLoader; }
      inline void            save(PResource) { }
  };
}

#endif //__ogl_cresource_hpp__
