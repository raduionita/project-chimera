#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl/ogl.hpp"

#include <unordered_map>
#include <cassert>

namespace ogl {
  class CResource { // loadable entity/file/object
    public:
      class CLoader { // loading strategy: .dds, .png, .md5, .3ds, .fxd, .obj, .mtl, .dae, .xml (generic), .csl
          // @todo: load async
          void load(bool async = false);
          virtual const char* extension() const = 0;
      };
      class CManager { // remembers and managegs loaded resources
        protected:
          std::unordered_map<std::string, CLoader*> mLoaders;
        public:
          template <typename T> T* loader(T*&& pLoader) {
            // multiple loaders for same .ext NOT allowed
            assert(mLoaders.count(pLoader->extension()) == 0);
            mLoaders[pLoader->extension()] = pLoader;
            return pLoader;
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
