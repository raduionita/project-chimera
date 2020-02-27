#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"
#include "sys/CCollection.hpp"

namespace ogl {
  class CTexture;        typedef sys::CPointer<CTexture>        PTexture; 
  class CTextureManager; typedef sys::CPointer<CTextureManager> PTextureManager;
  class CTextureStream;  typedef sys::CPointer<CTextureStream>  PTextureStream;
  template <typename T> class CTextureLoader; template <typename T> using PTextureLoader =  sys::CPointer<CTextureLoader<T>>;
  
  class CTexture : public ogl::CResource, public CObject { // or should this be CBuffer since it holds data/memory
      friend class CTextureStream;
      friend class CTextureManager;
    public:
      enum EFlag {
        FLAG           = 0b00000000'00000001,
        COLORMAP       = FLAG <<  1, // 2
        PLANEMAP       = FLAG <<  2, // 4
        CUBEMAP        = FLAG <<  3, // 8
        VOLUME         = FLAG <<  4,
        COMPRESSED     = FLAG <<  5,
        RGBA_S3TC_DXT1 = FLAG <<  6,
        RGBA_S3TC_DXT3 = FLAG <<  7,
        RGBA_S3TC_DXT5 = FLAG <<  8,
        RGBA           = FLAG <<  9,
        RGB            = FLAG << 10,
        LUMINANCE      = FLAG << 11,
        MIPMAPED       = FLAG << 12,
      };
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
        COLORMAP        = 0b00000000'10000000, //
        PLANEMAP        = 0b00000001'00000000, //
        CUBEMAP         = 0b00000010'00000000, //
        VOLUME          = 0b00000100'00000000  //
      };
      enum class EOptions   : GLbitfield {
        NONE            = 0b00000000'00000000, //
        MIPMAPS         = 0b00001000'00000000, //
      };
    protected:
      GLint   mSlot     {0};             // move to COGLTexture
      GLenum  mTarget   {GL_TEXTURE_2D}; // move to COGLTexture
      GLenum  mInternal {GL_NONE};       // move to COGLTexture
      GLenum  mFormat   {GL_NONE};
      EType   mType     {EType::PLANEMAP};
      GLsizei mWidth    {0};
      GLsizei mHeight   {0};
      GLsizei mDepth    {1};
      GLcount mMipmaps  {1};
    public:
      CTexture();
      CTexture(PTextureStream);
      ~CTexture();
    public: // actions
      virtual GLvoid   bind(bool=true) const override;
              GLvoid   bind(GLint);
      GLvoid           sampler(CShader*);
      virtual void     load(PTextureStream) final;
    public:
      // template <typename T> static PTexture from(const T& src) { return manager()->load(src); }
    public: // get/set-ers
      void          filtering(EFiltering eFiltering);
      EFiltering    filtering() const { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      void          wrapping(EWrapping eWrapping);
      inline GLenum target() const { return mTarget; }
      inline void   type(EType eType) { mType = eType; mTarget = (eType == EType::CUBEMAP ? GL_TEXTURE_CUBE_MAP : (eType == EType::VOLUME ? GL_TEXTURE_3D : mTarget)); }
      inline EType  type() const { return mType; }
      inline void   format(GLenum format) { mFormat = format; }
      inline GLenum format() const { return mFormat; }
      inline void   width(GLsizei w)   { mWidth  = w; }
      inline void   height(GLsizei h)  { mHeight = h; }
      inline void   depth(GLsizei d)   { mDepth  = d; }
      inline void   mipmaps(GLcount m) { mMipmaps = m == 0 ? 1 : m; }
      inline GLint  slot() const { return mSlot; }
      
      friend inline GLbitfield operator |(const CTexture::EWrapping&, const CTexture::EWrapping&);
      friend inline GLbitfield operator |(const CTexture::EFiltering&, const CTexture::EWrapping&);
  };
  
  inline GLbitfield operator |(const CTexture::EWrapping& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) | (GLbitfield)(rhs)); }
  inline GLbitfield operator |(const CTexture::EFiltering& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) | (GLbitfield)(rhs)); }
  
  // stream //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureStream : public ogl::CResourceStream {
      friend class CTexture;
      friend class CTextureManager;
    public:
      using ogl::CResourceStream::CResourceStream;
      using EFlag = CTexture::EFlag;
    public:
      struct SInfo {
        uint flags    {0};
        uint width    {0};
        uint height   {0};
        uint depth    {0};
        uint mipmaps  {1};
        uint size     {0};
        uint bpp     {32};
      };
    protected:
      SInfo mInfo;
    public:
      inline void set(EFlag flag) { mInfo.flags |= flag; }
      inline bool has(EFlag flag) { return mInfo.flags & flag; }
      inline void width(uint w)   { mInfo.width = w; }
      inline void height(uint h)  { mInfo.height = h; }
      inline void depth(uint d)   { mInfo.depth = d; }
      inline void mipmaps(uint m) { mInfo.mipmaps = m; }
    public:
      inline SInfo info() const         { return mInfo; }
      inline void  info(const SInfo& i) { mInfo = i; }
    public:
      static inline uint clamp2one(uint value) { return value < 1 ? 1 : value; }
      static inline uint texsize(uint width, uint height, uint depth, uint channels, uint faces, uint mipmaps) { return 0; }
      static inline uint mapsize(uint width, uint height, uint depth, uint channels, uint flags = 0) { return flags & CTexture::COMPRESSED ? (((width + 3) >> 2) * ((height + 3) >> 2) * depth * (flags & CTexture::RGBA_S3TC_DXT1 ? 8 : 16)) : (width * height * depth * channels); }
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template <typename T> class CTextureLoader : public ogl::CResourceLoader {
      friend class CTexture;
      friend class CTextureManager;
    public:
      virtual PTextureStream load(const T&) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
  };
  
  class CFileTextureLoader : public CTextureLoader<sys::CFile> {
      friend class CTexture;
      friend class CTextureStream;
      friend class CTextureManager;
    public:
      static inline const char* name() { return typeid(CTextureLoader<sys::CFile>).name(); }
      virtual PTextureStream load(const sys::CFile&) override;
  };
  
  // class CDdsTextureLoader : public CFileTextureLoader {
  //     enum {
  //       DDS_CAPS        = 0x00000001,
  //       DDS_HEIGHT      = 0x00000002,
  //       DDS_WIDTH       = 0x00000004,
  //       DDS_PITCH       = 0x00000008,
  //       DDS_PIXELFORMAT = 0x00001000,
  //       DDS_MIPMAPCOUNT = 0x00020000,
  //       DDS_LINEARSIZE  = 0x00080000,
  //       DDS_DEPTH       = 0x00800000,
  //       // pixel format flags
  //       DDS_ALPHAPIXELS = 0x00000001,
  //       DDS_FOURCC      = 0x00000004,
  //       DDS_RGB         = 0x00000040,
  //       DDS_RGBA        = 0x00000041,
  //       // caps1 flags
  //       DDS_COMPLEX     = 0x00000008,
  //       DDS_TEXTURE     = 0x00001000,
  //       DDS_MIPMAP      = 0x00400000,
  //       // caps2 flags
  //       DDS_CUBEMAP           = 0x00000200,
  //       DDS_CUBEMAP_POSITIVEX = 0x00000400,
  //       DDS_CUBEMAP_NEGATIVEX = 0x00000800,
  //       DDS_CUBEMAP_POSITIVEY = 0x00001000,
  //       DDS_CUBEMAP_NEGATIVEY = 0x00002000,
  //       DDS_CUBEMAP_POSITIVEZ = 0x00004000,
  //       DDS_CUBEMAP_NEGATIVEZ = 0x00008000,
  //       DDS_CUBEMAP_ALL_FACES = 0x0000FC00,
  //       DDS_VOLUME            = 0x00200000,
  //       //
  //       DDS_FOURCC_DTX1 = 0x31545844, // = DTX1(in ASCII)
  //       DDS_FOURCC_DTX3 = 0x33545844, // = DTX3(in ASCII)
  //       DDS_FOURCC_DTX5 = 0x35545844, // = DTX5(in ASCII)
  //     };
  //     struct SFormat {
  //       uint    size;
  //       uint    flags;
  //       uint    fourcc;
  //       uint    bpp;
  //       uint    rbitmask;
  //       uint    gbitmask;
  //       uint    bbitmask;
  //       uint    abitmask;
  //     };
  //     struct SHeader {
  //       uint    flags;
  //       uint    size;
  //       uint    height;
  //       uint    width;
  //       uint    linearsize;
  //       uint    depth;          // only if DDS_HEADER_FLAGS_VOLUME is in header_t::flags
  //       uint    mipmapcount;
  //       uint    _reserved1[11];
  //       SFormat format; 
  //       uint    caps1;
  //       uint    caps2;
  //       uint    _reserved2[3];
  //     };
  //     struct SDXTColBlock {
  //       ushort col0;
  //       ushort col1;
  //       utiny  row[4];
  //     };
  //     struct SDXT3AlphaBlock {
  //       ushort row[4];
  //     };
  //     struct SDXT5AlphaBlock {
  //       utiny alpha0;
  //       utiny alpha1;
  //       utiny row[6];
  //     };
  //   public:
  //     virtual inline const char* type() const override { return "dds"; }
  //     virtual PTextureStream     load(const sys::CFile& file) override;
  // }; 
  //
  // class CTgaTextureLoader : public CFileTextureLoader {
  //   public:
  //     virtual PTextureStream load(const sys::CFile&) override { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
  // };
  //
  //
  //
  // class CNoiseTextureLoader : public CTextureLoader { };
  // class CPerlinTextureLoader : public CTextureLoader { };
  // class CSimplexTextureLoader : public CTextureLoader { };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureManager : public ogl::CResourceManager, public sys::CSingleton<CTextureManager> {
      friend class CTexture;
      friend class CTextureStream;
    protected:
      std::map<sys::CString,ogl::PTexture> mTextures;
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      PTexture find(const sys::CString&) const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); }
      PTexture save(PTexture pTexture) { ogl::CResourceManager::save(pTexture); return pTexture; } 
      
      template <typename T> PTexture load(const sys::CString& name, const T& from) {
        log::nfo << "ogl::CTextureManager::load(CString&,T&)::" << this << log::end;
        PTexture pTexture;
        // try to find model in cache using that key
        auto it = mTextures.find(name);
        if (it != mTextures.end()) {
          pTexture = it->second;
        } else {
          PTextureStream           pStream;
          static PTextureLoader<T> pLoader = sys::static_pointer_cast<PTextureLoader<T>::type>(loader(typeid(CTextureLoader<T>).name()));
          // is the loader ok?
          if (pLoader) {
            // @todo: start on another thread
            pStream = pLoader->load(from);
            // @todo: queue `new CModel{pStream}` for the main thread 
            pTexture  = new CTexture{pStream};
            // update cache
            mTextures.insert({name, pTexture});
          }
        }
        // return texture
        return pTexture;
      }
      
      PTexture load(const sys::CString& name, PTextureStream stream) {
        log::nfo << "ogl::CTextureManager::load(CString&,PTextureStream)::" << this << " NAME:" << name << " STREAM: ?"  << log::end;
        
        return new CTexture{stream};
      }
  };
}

#endif //__ogl_ctexture_hpp__
