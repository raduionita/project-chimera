#ifndef __ogl_cresource_hpp__
#define __ogl_cresource_hpp__

#include "ogl.hpp"

namespace ogl {
  class CResource { // loadable entity/file/object
    public:
      class CLoader { // loading strategy: .dds, .png, .md5, .3ds, .fxd, .obj, .mtl, .dae, .xml
          
      };
      class CManager { // remembers and managegs loaded resources
          
      };
      // @todo: needs methods for defining load strategy and events on load/begin/finish/error/failed
  };
  
  // class CMaterial : CResource
  
  // class CTexture : CResource
  
  // class CModel : CResource
  
  // class CAnimation : CResource
}

#endif //__ogl_cresource_hpp__
