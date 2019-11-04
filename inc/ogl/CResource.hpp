#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>

namespace ogl {
  class CResourceLoader;
  class CResourceManager;
  
  class CResource { // loadable entity/file/object
      friend class CResourceLoader;
      friend class CResourceManager;
    public:
      // @todo: needs methods for defining load strategy and events on load/begin/finish/error/failed
  };
  
  class CResourceLoader {
      friend class CResourceManager;  
    public:
      CResourceLoader() { }
      virtual ~CResourceLoader() { }
    public:
      virtual bool able(const sys::CString& name) const = 0;
  };
  
  class CResourceManager { // remembers and managegs loaded resources
    protected:
      sys::CVector<ogl::CResourceLoader*> mLoaders;
    public:
      CResourceManager();
      virtual ~CResourceManager();
    public:
      template <typename T> const T* loader(T*&& pLoader, uint nPriority = uint(-1)) {
        // DO NOT allow other kind of loaders 
        static_assert(std::is_base_of<ogl::CResourceLoader,T>::value, "T is not a sub-class of ogl::CResourceLoader!");
        // overwrite priority
        if (nPriority != uint(-1)) pLoader->mPriority = nPriority; 
        // move loader to list of loaders
        mLoaders.push_back(std::move(pLoader));
        // return inserted
        return mLoaders.back();
      }
  };
  
  // class CMaterial : CResource
  
  // class CTexture : CResource
  
  // class CModel : CResource
  
  // class CAnimation : CResource
}

#endif //__ogl_cresource_hpp__
