#ifndef __ogl_crendersystem_hpp__
#define __ogl_crendersystem_hpp__

#include "ogl/ogl.hpp"

namespace ogl {
  class CRenderSystem; typedef sys::CPointer<CRenderSystem> PRenderSystem;
  
  struct SRenderOperation {
    
  };
  
  // @todo: there should be an extended version of this for each type of renderer OGL3 OGLES DX12 VLK
  
  class CRenderSystem {
    public:
      CRenderSystem();
      virtual ~CRenderSystem();
    public:
      virtual void render(const SRenderOperation& op);
  };
}

#endif //__ogl_crendersystem_hpp__
