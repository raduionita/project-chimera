#ifndef __cym_clayer_hpp__
#define __cym_clayer_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CLayer {
    protected:
      cym::CSurface* mSurface {nullptr};
    public:
      CLayer() = default;
      ~CLayer() = default;
  };
} // namespace cym


#endif //__cym_clayer_hpp__