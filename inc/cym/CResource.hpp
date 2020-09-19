#ifndef __cym_cresource_hpp__
#define __cym_cresource_hpp__

#include "cym/cym.hpp"
#include "sys/CException.hpp"
#include "sys/CStream.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>
#include <functional>
#include <any>

namespace cym {
  class CResource;        typedef sys::TPointer<CResource> PResource;
  class CResourceManager; typedef sys::TPointer<CResourceManager> PResourceManager;
  class CResourceInfo;    typedef sys::TPointer<CResourceInfo> PResourceStream;
  class CResourceLoader;  typedef sys::TPointer<CResourceLoader> PResourceLoader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceInfo;
      friend class CResourceManager;
      friend class CResourceLoader;
    public:
      CResource() = default;
      virtual ~CResource() = default;
  };
  
  class CResourceInfo {
      friend class CResource;
      friend class CResourceManager;
      friend class CResourceLoader;
    public:
      CResourceInfo() = default;
      virtual ~CResourceInfo() = default;
  };
  
  class CResourceLoader {
      friend class CResource;
      friend class CResourceInfo;
      friend class CResourceManager;
    public:
      CResourceLoader();
      virtual ~CResourceLoader();
    protected:
      static inline const char* type() { throw sys::CException("?Loader::type() NOT IMPLEMENTED", __FILE__, __LINE__); };
  };
  
  class CResourceManager {
      friend class CResource;
      friend class CResourceInfo;
      friend class CResourceLoader;
    private:
      sys::CString mScope;
    protected:
      sys::CMap<sys::CString, PResourceLoader> mLoaders;
    public:
      CResourceManager() = default;
      CResourceManager(const sys::CString&);
      virtual ~CResourceManager();
    public:
      const PResourceLoader& loader(const char* name) { return sys::find_or_throw(sys::CString(name),mLoaders,sys::CException("Loader NOT found!",__FILE__,__LINE__)); }
      
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CResourceLoader*>::value>::type> inline PResourceLoader loader() { return loader(typeid(T).name()); }
      
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CResourceLoader*>::value>::type> inline void loader(T* pLoader) { mLoaders[T::type()] = pLoader; /* mLoaders["P8CFileTextureLoader"] = pLoader */ }
      
      inline void            save(PResource) { }
  };
}

#endif //__cym_cresource_hpp__
