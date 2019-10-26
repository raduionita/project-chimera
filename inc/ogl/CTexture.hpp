#ifndef __glo_ctexture_hpp__
#define __glo_ctexture_hpp__

#include "glo.hpp"
#include "CObject.hpp"

namespace glo {
  class CTexture : public CObject { // or should this be CBuffer since it holds data/memory
    protected:
      GLenum mSlot {GL_TEXTURE0};
    public:
      CTexture();
      ~CTexture();
    public:
      void slot(GLenum slot = GL_NONE) {
        GLCALL(::glActiveTexture((slot == GL_NONE) ? (mSlot) : (mSlot = slot)));
      }
  };
}

#endif //__glo_ctexture_hpp__
