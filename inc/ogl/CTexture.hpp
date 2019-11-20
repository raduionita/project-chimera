#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"
#include "sys/CCollection.hpp"

namespace ogl {
  class CTexture;        typedef sys::CPointer<CTexture>        PTexture; 
  class CTextureManager; typedef sys::CPointer<CTextureManager> PTextureManager;
  class CTextureStream;  typedef sys::CPointer<CTextureStream>  PTextureStream;
  class CTextureReader;  typedef sys::CPointer<CTextureReader>  PTextureReader;
  
  class CTexture : public ogl::CResource, public CObject { // or should this be CBuffer since it holds data/memory
      friend class CTextureStream;
      friend class CTextureManager;
      friend class CTextureReader;
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
      CTexture(PTextureStream);
      CTexture(GLenum target);
      CTexture(EType type);
      ~CTexture();
    public: // actions
      virtual GLvoid   bind(bool=true) const override;
              GLvoid   bind(GLuint);
      GLvoid           sampler(CShader*);
      virtual void     load(PTextureStream) final;
    public:
      static  PTexture from(PTextureStream pStream) { return new CTexture(pStream); }
    public: // get/set-ers
      GLvoid        filtering(EFiltering eFiltering) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      EFiltering    filtering() const { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      inline GLenum target() const { return mTarget; }
      inline void   type(EType eType) { mType = eType; mTarget = (eType == EType::CUBEMAP ? GL_TEXTURE_CUBE_MAP : (eType == EType::VOLUME ? GL_TEXTURE_3D : mTarget)); }
      inline EType  type() const { return mType; }
      inline void   format(GLenum format) { mFormat = format; }
      inline GLenum format() const { return mFormat; }
      inline void   width(GLsizei w)   { mWidth  = w; }
      inline void   height(GLsizei h)  { mHeight = h; }
      inline void   depth(GLsizei d)   { mDepth  = d; }
      inline void   mipmaps(GLcount m) { mMipmaps = m == 0 ? 1 : m; }
  };
  
  class CTextureStream : public CResourceStream {
      friend class CTexture;
      friend class CTextureManager;
      friend class CTextureReader;
    protected:
      // meta
      uint   mWidth;
      uint   mHeight;
      uint   mDepth;
      size_t mSize;
      uint   mMipmaps;
      uint   mFlags;
      uint   mFormat;
      uint   mType;
      // data
      ubyte* mStart;
      ubyte* mCursor;
      ubyte* mLast;
    public:
      inline PTexture load()                   { PTexture pTexture = new CTexture; pTexture->load(this); return pTexture; }
      inline PTexture load(PTexture pTexture)  { if (!pTexture) pTexture = new CTexture; pTexture->load(this); return pTexture; }
      inline PTexture load(CTexture* pTexture) { pTexture->load(this); return pTexture; }
  };
  
  class CTextureManager : public ogl::CResourceManager, public sys::CSingleton<CTextureManager> {
      friend class CTexture;
      friend class CTextureStream;
      friend class CTextureReader;
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      PTexture load(PTextureStream, const sys::CString& = "") const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); }
      PTexture load(const sys::CFile& file, const sys::CString& = "");
      PTexture find(const sys::CString&) const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); }
      void     save(PTexture pTexture) { ogl::CResourceManager::save(pTexture); } 
  };
  
  class CTextureReader : public CResourceReader {
      friend class CTexture;
      friend class CTextureStream;
      friend class CTextureManager;
    public:
      virtual PTextureStream read(const sys::CFile&) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
  };
  
  class CDdsTextureReader : public CTextureReader {
      enum {
        DDS_CAPS        = 0x00000001,
        DDS_HEIGHT      = 0x00000002,
        DDS_WIDTH       = 0x00000004,
        DDS_PITCH       = 0x00000008,
        DDS_PIXELFORMAT = 0x00001000,
        DDS_MIPMAPCOUNT = 0x00020000,
        DDS_LINEARSIZE  = 0x00080000,
        DDS_DEPTH       = 0x00800000,
        // pixel format flags
        DDS_ALPHAPIXELS = 0x00000001,
        DDS_FOURCC      = 0x00000004,
        DDS_RGB         = 0x00000040,
        DDS_RGBA        = 0x00000041,
        // caps1 flags
        DDS_COMPLEX     = 0x00000008,
        DDS_TEXTURE     = 0x00001000,
        DDS_MIPMAP      = 0x00400000,
        // caps2 flags
        DDS_CUBEMAP           = 0x00000200,
        DDS_CUBEMAP_POSITIVEX = 0x00000400,
        DDS_CUBEMAP_NEGATIVEX = 0x00000800,
        DDS_CUBEMAP_POSITIVEY = 0x00001000,
        DDS_CUBEMAP_NEGATIVEY = 0x00002000,
        DDS_CUBEMAP_POSITIVEZ = 0x00004000,
        DDS_CUBEMAP_NEGATIVEZ = 0x00008000,
        DDS_CUBEMAP_ALL_FACES = 0x0000FC00,
        DDS_VOLUME            = 0x00200000,
        //
        DDS_FOURCC_DTX1 = 0x31545844, // = DTX1(in ASCII)
        DDS_FOURCC_DTX3 = 0x33545844, // = DTX3(in ASCII)
        DDS_FOURCC_DTX5 = 0x35545844, // = DTX5(in ASCII)
      };
      struct SFormat {
        uint    size;
        uint    flags;
        uint    fourcc;
        uint    bpp;
        uint    rbitmask;
        uint    gbitmask;
        uint    bbitmask;
        uint    abitmask;
      };
      struct Sheader {
        uint    flags;
        uint    size;
        uint    height;
        uint    width;
        uint    linearsize;
        uint    depth;          // only if DDS_HEADER_FLAGS_VOLUME is in header_t::flags
        uint    mipmapcount;
        uint    _reserved1[11];
        SFormat format; 
        uint    caps1;
        uint    caps2;
        uint    _reserved2[3];
      };
    public:
      virtual inline const char* type() const override { return "dds"; }
      virtual PTextureStream     read(const sys::CFile&) override;
  }; 
  
  class CTgaTextureReader : public CTextureReader {
    public:
      virtual PTextureStream read(const sys::CFile&) override { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); }
  };
}

#endif //__ogl_ctexture_hpp__
