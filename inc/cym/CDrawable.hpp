#ifndef __cym_cdrawable_hpp__
#define __cym_cdrawable_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CDrawable {
      // virtual CMaterial* material() const = 0; 
      // virtual CTehnique* technique() const = 0; // material()->technique()
      // virtual COperation operation() = 0; // render operation required to send this to the framebuffer
      // 
    public:
      virtual void draw() = 0;
  };
}

#endif //__cym_cdrawable_hpp__

