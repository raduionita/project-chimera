#ifndef __cym_crendersystem_hpp__
#define __cym_crendersystem_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CRenderSystem; typedef sys::TPointer<CRenderSystem> PRenderSystem;
  
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

#endif //__cym_crendersystem_hpp__
