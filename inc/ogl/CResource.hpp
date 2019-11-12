#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>
#include <functional>

namespace ogl {
  class CResource;        typedef sys::CPointer<CResource>        PResource;
  class CResourceManager; typedef sys::CPointer<CResourceManager> PResourceManager;
  class CResourceStream;  typedef sys::CPointer<CResourceStream>  PResourceStream;
  class CResourceLoader;  typedef sys::CPointer<CResourceLoader>  PResourceLoader;
  
  class CResource { // loadable entity/file/object
      friend class CResourceManager;
      friend class CResourceStream;
    public:
      
  };
  
  class CResourceStream {
      friend class CResource;
      friend class CResourceLoader;
      friend class CResourceManager;
  };
  
  class CResourceManager { // remembers and managegs loaded resources
      friend class CResource;
      friend class CResourceStream;
      friend class CResourceLoader;
    protected:
      sys::CVector<ogl::CResourceLoader*> mLoaders;
      // sys::CMap<sys::CString, TLoader> mLoaders;
    public:
      CResourceManager();
      virtual ~CResourceManager();
    public:
      template <typename T> const T* loader(T*&& pLoader) {
        // DO NOT allow other kind of loaders 
        static_assert(std::is_base_of<ogl::CResourceLoader,T>::value, "T is not a sub-class of ogl::CResourceLoader!");
        // move loader to list of loaders
        mLoaders.push_back(std::move(pLoader));
        // return inserted
        return mLoaders.back();
      }
  };
  
  class CResourceLoader {
      friend class CResource;
      friend class CResourceManager;
      friend class CResourceStream;
    public:
      CResourceLoader() = default;
      virtual ~CResourceLoader() = default;
    public:
      virtual inline bool able(const sys::CString&) const = 0;
  };
}

#endif //__ogl_cresource_hpp__
