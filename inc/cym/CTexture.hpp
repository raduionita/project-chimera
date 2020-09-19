#ifndef __cym_ctexture_hpp__
#define __cym_ctexture_hpp__

#include "cym/cym.hpp"
#include "cym/CObject.hpp"
#include "cym/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"
#include "glm/CVector.hpp"
#include "cym/CNode.hpp"

namespace cym {
  class CTexture;        typedef sys::TPointer<CTexture> PTexture; 
  class CTextureManager; typedef sys::TPointer<CTextureManager> PTextureManager;
  class CTextureData;    typedef sys::TPointer<CTextureData> PTextureData;
  template<typename T> class CTextureLoader; template<typename T> using PTextureLoader =  sys::TPointer<CTextureLoader<T>>;
  
  // texture /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CColor {
    public:
      glm::vec3 mColor;
  };
  
  class CTexture : public cym::CResource, public CObject { // or should this be CBuffer since it holds data/memory
      friend class CTextureData;
      friend class CTextureManager;
    public:
      enum EFlag {
        FLAG           = 0b00000000'00000001, // 2^0 = 1
        COLORMAP       = FLAG <<  1,          //     = 2
        PLANEMAP       = FLAG <<  2,          //     = 4
        CUBEMAP        = FLAG <<  3,          //     = 8
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
      CTexture(PTextureData);
      ~CTexture();
    public: // actions
      virtual GLvoid   bind(bool=true) const override;
              GLvoid   bind(GLint);
      GLvoid           sampler(CShader*);
      virtual void     load(PTextureData) final;
    public:
      // template<typename T> static PTexture from(const T& src) { return manager()->load(src); }
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
  
  // int w, h;
  // int miplevel = 0;
  // glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
  // glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);

  class NTexture : public TNode<cym::CTexture> {
    protected:
    //cym::PChannel mResource;
  };
  
  // data ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureData : public cym::CResourceInfo {
      friend class CTexture;
      friend class CTextureManager;
    public:
      using cym::CResourceInfo::CResourceInfo;
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
    public:
      SInfo        mInfo;
      sys::PStream mStream;
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
      static inline uint size(uint width, uint height, uint depth, uint channels, uint flags = 0) { return flags & CTexture::COMPRESSED ? (((width + 3) >> 2) * ((height + 3) >> 2) * depth * (flags & CTexture::RGBA_S3TC_DXT1 ? 8 : 16)) : (width * height * depth * channels); }
  };
  
  struct STextureInfo {
    using EFlag = CTexture::EFlag;
  // identifier
    sys::string  name;
  // load
    sys::PStream stream;
    sys::file    file;
  // fields
    uint flags    {0};
    uint width    {0};
    uint height   {0};
    uint depth    {0};
    uint mipmaps  {1};
    uint size     {0};
    uint bpp     {32};
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> class CTextureLoader : public cym::CResourceLoader {
      friend class CTexture;
      friend class CTextureManager;
    public:
      ~CTextureLoader() { log::nfo << "cym::CTextureLoader::~CTextureLoader()::" << this << log::end; }
    public:
      virtual PTextureData load(const T&) { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); };
  };
  
  class CFileTextureLoader : public CTextureLoader<sys::CFile> {
      friend class CTexture;
      friend class CTextureData;
      friend class CTextureManager;
    protected:
      sys::CMap<sys::CString, PCodec> mCodecs;
    public:
      CFileTextureLoader();
      ~CFileTextureLoader();
    protected:
      template<typename T, class = typename std::enable_if<std::is_convertible<T*,CCodec*>::value>::type> inline void codec(T* pCodec) { mCodecs[pCodec->type()] = pCodec; }
      PCodec codec(const sys::CString& ext);
    public:
      static inline const char* type() { return typeid(CTextureLoader<sys::CFile>).name(); }
      virtual PTextureData      load(const sys::CFile&) override;
  };
  
  class CNoiseTextureLoader : public CTextureLoader<int/*noise_descriptor*/> { };
  // class CPerlinTextureLoader : public CTextureLoader { };
  // class CSimplexTextureLoader : public CTextureLoader { };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureManager : public cym::CResourceManager, public sys::TSingleton<CTextureManager> {
      friend class CTexture;
      friend class CTextureData;
    protected:
      sys::CMap<sys::CString,cym::PTexture> mTextures;
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      PTexture find(const sys::CString&) const { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); }
      PTexture save(PTexture pTexture) { cym::CResourceManager::save(pTexture); return pTexture; } 
      
      template<typename T> PTexture load(const sys::CString& name, const T& from) {
        log::nfo << "cym::CTextureManager::load(CString&,T&)::" << this << log::end;
        PTexture pTexture;
        // try to find model in cache using that key
        auto it = mTextures.find(name);
        if (it != mTextures.end()) {
          pTexture = it->second;
        } else {
          static const PTextureLoader<T>& pLoader{sys::static_pointer_cast<typename PTextureLoader<T>::type>(loader(typeid(CTextureLoader<T>).name()))};
          
          // @todo: start on another thread
          PTextureData pData = pLoader->load(from);
          // @todo: queue `new CModel{pStream}` for the main thread 
          pTexture = new CTexture{pData};
          // update cache
          mTextures.insert({name, pTexture});
        }
        // return texture
        return pTexture;
      }
  };

  // utils ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  inline uint mapsize(uint width, uint height, uint depth, uint channels, uint flags = 0) { return flags & CTexture::COMPRESSED ? (((width + 3) >> 2) * ((height + 3) >> 2) * depth * (flags & CTexture::RGBA_S3TC_DXT1 ? 8 : 16)) : (width * height * depth * channels); }
}

#endif //__cym_ctexture_hpp__
