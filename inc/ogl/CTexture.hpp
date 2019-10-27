#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CSingleton.hpp"

namespace ogl {
  class CTexture : public CResource, public CObject { // or should this be CBuffer since it holds data/memory
    public:
      class CLoader : public CResource::CLoader {
          // CDdsLoader : CTexture::CLoader
          // CDataLoader : CTexture::CLoader
      };
      class CManager : public CResource::CManager, public sys::CSingleton<CManager> {
        public:
          CTexture* load(const std::string& file);
          CTexture* find(GLuint id);
      };
    protected:
      GLenum mSlot {0};
    public:
      CTexture();
      ~CTexture();
    public:
      GLuint activate(GLuint slot = GL_NOT_FOUND) {
        GLCALL(::glActiveTexture(GL_TEXTURE0 + ((slot == GL_NOT_FOUND) ? (mSlot) : (mSlot = slot))));
        return mSlot;
      }
  };
}

#endif //__ogl_ctexture_hpp__
