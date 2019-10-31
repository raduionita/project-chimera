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
        public:
          CLoader();
        public:
          virtual bool able(const sys::CString& file) override;
      };
    public:
      class CManager : public CResource::CManager, public sys::CSingleton<CManager> {
        public:
          CManager();
          ~CManager();
        public:
          CTexture* load(const CString& name);
          CTexture* load(const CString& name, const CLoader*& loader);
          CTexture* find(GLuint id);
      };
    public:
      enum class EFiltering : GLbitfield {
        NONE            = 0b00000000'00000000, // 0
        NEAREST         = 0b00000000'00000001, // 1
        BILINEAR        = 0b00000000'00000010, // 2
        TRILINEAR       = 0b00000000'00000100, // 4
        ANISOTROPIC     = 0b00000000'00001000  // 8
      };
      enum class EWrapping  : GLbitfield {
        NONE            = 0b00000000'00000000, // 0
        CLAMP_TO_EDGE   = 0b00000000'00010000, // 16
        CLAMP_TO_BORDER = 0b00000000'00100000, // 32
        REPEAT          = 0b00000000'01000000, // 64
      };
      enum class EType      : GLbitfield {
        NONE            = 0b00000000'00000000, //
        FLAT            = 0b00000000'10000000, //
        CUBEMAP         = 0b00000001'00000000, //
        VOLUME          = 0b00000010'00000000  //
      };
      enum class EOptions   : GLbitfield {
        NONE            = 0b00000000'00000000, //
        MIPMAPS         = 0b00000100'00000000, //
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
  
  class CDepthTexture : public CTexture { 
      
  };
  
  class CNullTexture : public CTexture {
      
  };
  

}

#endif //__ogl_ctexture_hpp__
