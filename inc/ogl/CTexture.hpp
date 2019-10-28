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
      enum class EFiltering : GLbitfield {
        NONE        = 0b0000'0000'0000, // 0
        NEAREST     = 0b0000'0000'0001, // 1
        BILINEAR    = 0b0000'0000'0010, // 2
        TRILINEAR   = 0b0000'0000'0100, // 4
        ANISOTROPIC = 0b0000'0000'1000  // 8
      };
      enum class EWrapping : GLbitfield {
        NONE            = 0b0000'0000'0000, // 0
        CLAMP_TO_EDGE   = 0b0000'0001'0000, // 16
        CLAMP_TO_BORDER = 0b0000'0010'0000, // 32
        REPEAT          = 0b0000'0100'0000, // 64
      };
      enum class EType : GLbitfield {
        NONE    = 0b0000'0000'0000, // 
        FLAT    = 0b0000'1000'0000, // 
        CUBEMAP = 0b0001'0000'0000, // 
        VOLUME  = 0b0010'0000'0000  // 
      };
    protected:
      GLenum mSlot   {0};
      GLenum mTarget {GL_TEXTURE_2D};
    public:
      CTexture();
      ~CTexture();
    public: // actions
      GLuint activate(GLuint slot = GL_NOT_FOUND);
      void   mipmap();
      void   sampler(CShader*);
    public: // get/set-ers
      void       filtering(EFiltering eFiltering);
      EFiltering filtering() const;
  };
  
  class CDdsLoader : public CTexture::CLoader {
      
  };
}

#endif //__ogl_ctexture_hpp__
