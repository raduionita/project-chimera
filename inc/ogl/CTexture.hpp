#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
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
      GLcount mMipmaps  {0};
    public:
      CTexture();
      CTexture(GLenum target);
      CTexture(EType type);
      CTexture(const CTextureLoader&, const sys::CString&);
      ~CTexture();
    public: // actions
      virtual GLvoid bind(bool=true) const override;
              GLvoid bind(GLuint);
      virtual void   load(const PTextureData&) final;
      GLvoid  sampler(CShader*);
    public: // get/set-ers
      GLvoid     filtering(EFiltering eFiltering);
      EFiltering filtering() const;
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
      
  };
  
  class CTextureLoader : public CResourceLoader {
    public:
      virtual bool     able(const sys::CString& name) const = 0;
      virtual PTexture load(const sys::CString& name) const = 0;
  };
  
  class CDDSTextureLoader : public CTextureLoader {
    private:
      typedef struct {
        ulong size;
        ulong flags;
        ulong fourcc;
        ulong bpp;
        ulong rbitmask;
        ulong gbitmask;
        ulong bbitmask;
        ulong abitmask;
      } pixelformat_t;
      typedef struct {
        ulong         size;
        ulong         flags;
        ulong         height;
        ulong         width;
        ulong         linearsize;
        ulong         depth;          // only if DDS_HEADER_FLAGS_VOLUME is in header_t::flags
        ulong         mipmaps;
        ulong         reserved1[11];
        pixelformat_t pf; 
        ulong         caps1;
        ulong         caps2;
        ulong         reserved2[3];
      } header_t;
    private:
      enum EFlag {
        // surface description flags
        CAPS         = 0x00000001,
        HEIGHT       = 0x00000002,
        WIDTH        = 0x00000004,
        PITCH        = 0x00000008,
        PIXELFORMAT  = 0x00001000,
        MIPMAPCOUNT  = 0x00020000,
        LINEARSIZE   = 0x00080000,
        DEPTH        = 0x00800000,
    
        // pixel format flags
        ALPHAPIXELS  = 0x00000001,
        FOURCC       = 0x00000004,
        RGB          = 0x00000040,
        RGBA         = 0x00000041,
    
        // caps1 flags
        COMPLEX      = 0x00000008,
        TEXTURE      = 0x00001000,
        MIPMAP       = 0x00400000,
    
        // caps2 flags
        CUBEMAP            = 0x00000200,
        CUBEMAP_POSITIVEX  = 0x00000400,
        CUBEMAP_NEGATIVEX  = 0x00000800,
        CUBEMAP_POSITIVEY  = 0x00001000,
        CUBEMAP_NEGATIVEY  = 0x00002000,
        CUBEMAP_POSITIVEZ  = 0x00004000,
        CUBEMAP_NEGATIVEZ  = 0x00008000,
        CUBEMAP_ALL_FACES  = 0x0000FC00,
        VOLUME             = 0x00200000,
    
        FOURCC_DTX1  = 0x31545844, // = DTX1(in ASCII)
        FOURCC_DTX3  = 0x33545844, // = DTX3(in ASCII)
        FOURCC_DTX5  = 0x35545844, // = DTX5(in ASCII)
      };
    public:
      virtual bool     able(const sys::CString& name) const override;
      virtual PTexture load(const sys::CString& name) const override;
    private:
      static inline uint clamp2one(uint val) { return val < 1 ? 1 : val; } 
      static inline uint mapsize(uint width, uint height, uint depth, uint components, uint format, bool compressed = true) { return compressed ? ((width + 3) >> 2) * ((height + 3) >> 2) * depth * (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16) : width * height * depth * components; }
  };  
  
  class CTGATextureLoader : public CTextureLoader {
    public:
      virtual bool     able(const sys::CString& name) const override;
      virtual PTexture load(const sys::CString& name) const override;
  };
  
  class CTextureManager : public CResourceManager, public sys::CSingleton<CTextureManager> {
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      CTexture* load(const sys::CString& name);
  };
}

#endif //__ogl_ctexture_hpp__
