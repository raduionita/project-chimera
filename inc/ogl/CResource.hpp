#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"
#include "sys/CException.hpp"
#include "sys/CStream.hpp"

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
  
  class CResourceStream : public sys::CStream {
      friend class CResource;
      friend class CResourceManager;
      friend class CResourceLoader;
    public:
      using sys::CStream::CStream;
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
      static const char* name() { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
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
      PResourceLoader loader(const char* name) {
        auto it = mLoaders.find(name);
        if (it != mLoaders.end()) {
          return it->second;
        }
        return nullptr;
      }
      
      template <typename T, class = typename std::enable_if<std::is_convertible<T*,CResourceLoader*>::value>::type> inline void loader(T* pLoader) {
        // mLoaders["P8CFileTextureLoader"] = pLoader
        mLoaders[T::name()] = pLoader; 
      }
      
      inline void            save(PResource) { }
  };
}

#endif //__ogl_cresource_hpp__
