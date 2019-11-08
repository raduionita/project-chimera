#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CSingleton.hpp"

namespace ogl {
  class CTexture;
  class CTextureManager;
  class CTextureLoader;
  class CTextureData;
  
  class CTexture : public CResource, public CObject { // or should this be CBuffer since it holds data/memory
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
        LUMINANCE       = 0b00000000'10000000, //
        FLATMAP         = 0b00000001'00000000, //
        CUBEMAP         = 0b00000010'00000000, //
        VOLUME          = 0b00000100'00000000  //
      };
      enum class EOptions   : GLbitfield {
        NONE            = 0b00000000'00000000, //
        MIPMAPS         = 0b00001000'00000000, //
      };
    protected:
      GLuint  mSlot     {0};             // move to COGLTexture
      GLenum  mTarget   {GL_TEXTURE_2D}; // move to COGLTexture
      GLenum  mInternal {GL_NONE};       // move to COGLTexture
      GLenum  mFormat   {GL_NONE};
      EType   mType     {EType::FLATMAP};
      GLsizei mWidth    {0};
      GLsizei mHeight   {0};
      GLsizei mDepth    {1};
      GLcount mMipmaps  {1};
    public:
      CTexture();
      CTexture(GLenum target);
      CTexture(EType type);
      ~CTexture();
    public: // actions
      virtual GLvoid bind(bool=true) const override;
              GLvoid bind(GLuint);
      GLvoid         sampler(CShader*);
      virtual void   load(const CTextureData*&) final;
    public: // get/set-ers
      GLvoid        filtering(EFiltering eFiltering);
      EFiltering    filtering() const;
      inline GLenum target() const { return mTarget; }
      inline void   type(EType eType) { mType = eType; mTarget = (eType == EType::CUBEMAP ? GL_TEXTURE_CUBE_MAP : (eType == EType::VOLUME ? GL_TEXTURE_3D : mTarget)); }
      inline EType  type() const { return mType; }
      inline void   format(GLenum format) { mFormat = format; }
      inline GLenum format() const { return mFormat; }
      inline void   width(GLsizei w)  { mWidth  = w; }
      inline void   height(GLsizei h) { mHeight = h; }
      inline void   depth(GLsizei d)  { mDepth  = d; }
      inline void   mipmaps(GLcount m)  { mMipmaps = m == 0 ? 1 : m; }
  };
  
  class CTextureData : public CResourceData {
    protected:
      // meta
      uint   mWidth;
      uint   mHeight;
      uint   mDepth;
      size_t mSize;
      uint   mMipmaps;
      uint   mFlags;
      uint   mFormat;
      // data
      ubyte* mStart;
      ubyte* mCursor;
      ubyte* mLast;
  };
  
  class CTextureLoader : public CResourceLoader {
    public:
      virtual bool     able(const sys::CString& name) const;
      virtual PTexture load(const sys::CFile& name) const;
  };
  
  class CTextureManager : public CResourceManager, public sys::CSingleton<CTextureManager> {
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      PTexture load(const sys::CString& name);
  };
}

#endif //__ogl_ctexture_hpp__
