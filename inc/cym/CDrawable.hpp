#ifndef __cym_cdrawable_hpp__
#define __cym_cdrawable_hpp__

#include "cym/cym.hpp"

namespace cym {
  
// @todo: this should return a drawcall w/ all the info needed
  
  class CDrawcall {
    protected:
      GLuint mVAO;
  };
  
  class CDebugcall {
      
  };
  
// @todo: same as drawable but for editor: icon + bbox + wireframe + flat-shaded + normals
  class CDebugable {
      
  };

  class CDrawable {
      // virtual CMaterial* material() const = 0; 
      // virtual CTehnique* technique() const = 0; // material()->technique()
      // virtual COperation operation() = 0; // render operation required to send this to the framebuffer
      // 
    public:
      virtual void draw() = 0;
      
// @todo:  who extends CDrawable must declare getDrawcall() and return a CDrawcall object w/ necessary info
    //virtual CDrawcall getDrawcall() = 0;
  };
}

#endif //__cym_cdrawable_hpp__

