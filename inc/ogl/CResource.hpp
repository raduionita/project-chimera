#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"

#include <unordered_map>
#include <cassert>
#include <type_traits>

namespace ogl {
  class CResource { // loadable entity/file/object
    public:
      class CManager;
      class CLoader {
          friend class CManager;  
        private:
          uint mPriority {uint(-1)};
        public:
          CLoader(uint nPriority = uint(-1)) { }
          virtual ~CLoader() { }
        public:
          virtual bool able(const sys::CString& file) = 0;
      };
      class CManager { // remembers and managegs loaded resources
        protected:
          sys::CVector<ogl::CResource::CLoader*> mLoaders;
        public:
          template <typename T> const T* loader(T*&& pLoader, uint nPriority = uint(-1)) {
            // DO NOT allow other kind of loaders 
            static_assert(std::is_base_of<CLoader,T>::value, "T is not a sub-class of ogl::CResource::CLoader!");
            // overwrite priority
            if (nPriority != uint(-1)) pLoader->mPriority = nPriority; 
            // move loader to list of loaders
            mLoaders.push_back(std::move(pLoader));
            // return inserted
            return mLoaders.back();
          }
      };
      // @todo: needs methods for defining load strategy and events on load/begin/finish/error/failed
  };
  
  // class CMaterial : CResource
  
  // class CTexture : CResource
  
  // class CModel : CResource
  
  // class CAnimation : CResource
}

#endif //__ogl_cresource_hpp__
