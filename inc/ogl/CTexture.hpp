#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CSingleton.hpp"

namespace ogl {
  class CTexture : public CResource, public CObject { // or should this be CBuffer since it holds data/memory
    public:
      class CManager : public CResource::CManager, public sys::CSingleton<CManager> {
        public:
          CTexture* load(const std::string& file);
      };
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

#endif //__ogl_ctexture_hpp__
