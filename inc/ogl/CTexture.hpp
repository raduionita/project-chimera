#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CSingleton.hpp"

namespace ogl {
  class CTexture : public CResource, public CObject { // or should this be CBuffer since it holds data/memory
    public:
      class CData {
          // @todo: CTextureData
      };
    public:
      class CLoader : public CResource::CLoader {
          // CDdsLoader : CTexture::CLoader
          // CDataLoader : CTexture::CLoader
      };
    public:
      class CManager : public CResource::CManager, public sys::CSingleton<CManager> {
        public:
          CTexture* load(const std::string& file);
          CTexture* find(GLuint id);
      };
    public:
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
      enum class EOptions : GLbitfield {
        NONE    = 0b0000'0000'0000, //
        MIPMAPS = 0b0100'0000'0000, //
      };
    protected:
      GLuint  mSlot     {0};
      GLenum  mTarget   {GL_TEXTURE_2D};
      GLenum  mInternal {GL_NONE};
      GLenum  mFormat   {GL_NONE};
      GLenum  mType     {GL_FLOAT};
      GLsizei mWidth    {0};
      GLsizei mHeight   {0};
      GLsizei mDepth    {1};
      GLcount mMipmaps  {0};
    public:
      CTexture();
      ~CTexture();
    public: // actions
      virtual GLvoid bind(bool=true) const override;
              GLvoid bind(GLuint);
      GLvoid  sampler(CShader*);
    public: // get/set-ers
      GLvoid     filtering(EFiltering eFiltering);
      EFiltering filtering() const;
  };
  
  class CDdsLoader : public CTexture::CLoader {
      
  };
}

#endif //__ogl_ctexture_hpp__
