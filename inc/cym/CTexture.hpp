#ifndef __cym_ctexture_hpp__
#define __cym_ctexture_hpp__

#include "cym/cym.hpp"
#include "cym/CObject.hpp"
#include "cym/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"
#include "sys/CThreader.hpp"
#include "cym/CInstance.hpp"
#include "glm/CVector.hpp"
#include "ogl/CTexture.hpp"

namespace cym {
  class CTexture;        
  class CTextureManager;
  class CTextureLoader;
  template<typename T> class TTextureLoader;
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTexture : public cym::CResource, /* @todo: ogl::CTexture */ public CObject { // or should this be CBuffer since it holds data/memory
      friend class CTextureLoader;
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
        BGRA           = FLAG << 11,
        BGR            = FLAG << 12,
        LUMINANCE      = FLAG << 13,
        MIPMAPED       = FLAG << 14,
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
      GLenum  mInternal {GL_RGBA};       // move to COGLTexture
      GLenum  mFormat   {GL_RGBA};
      EType   mType     {EType::PLANEMAP};
      GLsizei mWidth    {0};
      GLsizei mHeight   {0};
      GLsizei mDepth    {1};
      GLcount mMipmaps  {1};
    public:
      using cym::CResource::CResource;
    public:
      CTexture(const std::string& = "");
      CTexture(sys::sptr<CTextureLoader>);
      ~CTexture();
    public: // actions
      virtual GLvoid   bind(bool=true) const override;
              GLvoid   bind(GLint);
      GLvoid           sampler(CShader*);
      virtual void     load(sys::sptr<CTextureLoader>) final;
    public:
      // template<typename T> static PTexture from(const T& src) { return manager()->init(src); }
    public: // get/set-ers
      void          filtering(EFiltering eFiltering);
      EFiltering    filtering() const { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      void          setWrapping(EWrapping eWrapping) const;
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
  inline GLbitfield operator &(const CTexture::EWrapping& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) & (GLbitfield)(rhs)); }
  inline GLbitfield operator |(const CTexture::EFiltering& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) | (GLbitfield)(rhs)); }
  inline GLbitfield operator &(const CTexture::EFiltering& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) & (GLbitfield)(rhs)); }
  
  // int w, h;
  // int miplevel = 0;
  // glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
  // glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
  
  // instances ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class ITexture : public cym::TInstance<CTexture> {
      friend class CTexture;
    public:
      using cym::TInstance<CTexture>::TInstance;
    public:
      inline const CTexture& getTexture() const { return mInstance.raw(); }
  };
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureLoader : public cym::CResourceLoader {
      friend class CTexture;
      friend class CTextureManager;
    public:
      using EFlag = CTexture::EFlag;
      enum EHint { MIPMAPS = 1 };
    public:
      sys::sptr<sys::CStream> mStream;
    // properties
      uint         flags   {0};
      uint         width   {0};
      uint         height  {0};
      uint         depth   {1};
      uint         mipmaps {1};
      uint         size    {0};
      ubyte        bpp    {32};
      bool         alpha  {false};
    public:
      using cym::CResourceLoader::CResourceLoader;
    public:
      virtual inline void         load(sys::sptr<CResourceLoader>) { throw sys::exception("CTextureLoader::load() NOT overriden!",__FILE__,__LINE__);  };
    public:
      template<typename T> inline static sys::sptr<TTextureLoader<T>> from(const T& tSource) { return new TTextureLoader<T>{tSource}; }
      template<typename T> inline static cym::name                    name(const T& tSource) { return TTextureLoader<T>::name(tSource); }
    public:
      inline sys::sptr<sys::CStream>& getStream() { return mStream; }
  };
  
  template<typename T> class TTextureLoader : public cym::CTextureLoader { };
  
  template<> class TTextureLoader<sys::CFile> : public CTextureLoader {
      friend class CTexture;
      friend class CTextureManager;
    protected:
      sys::CFile mFile;
    public:
      TTextureLoader(const sys::CFile& tFile) : CTextureLoader(tFile.path()), mFile{tFile} { };
    public:
      virtual void load(sys::sptr<CResourceLoader>) override;
    public:
      inline static cym::name name(const sys::CFile& tFile) { return tFile.path(); }
    public:
      sys::CFile& getFile() { return mFile; }
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureManager : public cym::CResourceManager, public sys::TSingleton<CTextureManager> {
      friend class CTexture;
      friend class CTextureLoader;
    protected:
      sys::CMap<std::string, sys::sptr<CTexture>> mTextures;
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      /* remeber/cache texture  */
      static void save(sys::sptr<CTexture> pTexture) {
        static auto pThis {CTextureManager::getSingleton()};
        CYM_LOG_NFO("cym::CTextureManager::save(sys::sptr<CTexture>)::" << pThis);
        pThis->mTextures.insert(std::pair(pTexture->mName, pTexture));
      }
      /* load texture from texture loader */
      static sys::sptr<CTexture> load(sys::sptr<CTextureLoader> pTextureLoader) {
        static auto pThis {cym::CTextureManager::getSingleton()};
        CYM_LOG_NFO("cym::CTextureManager::load(sys::sptr<CTextureLoader>)::" << pThis);
        
        if (!pTextureLoader) return nullptr;
        
        sys::sptr<CTexture> pTexture = new CTexture{pTextureLoader->getName()};
        
        sys::async([&pTexture, pTextureLoader](){
          
          pTextureLoader->load(pTextureLoader);
          
// @todo: load tex ASAP using lowes rez/mip, ASYNC the rest of the mips/high-rez
          
          pTexture->load(pTextureLoader);
          
        }, sys::EAsync::SPAWN);
        
        CTextureManager::save(pTexture);
        
        return pTexture;
      }
      /* = load(sys::CFile{"path/to/texture.tex"}) */
      template<typename T> static sys::sptr<ITexture> load(const T& tSource) {
        static auto pThis {cym::CTextureManager::getSingleton()};
        CYM_LOG_NFO("cym::CTextureManager::load(T&)::" << pThis);
      
        sys::sptr<CTexture> tTexture;
        const std::string&  tName = CTextureLoader::name(tSource);
        
        if (!sys::find(tName, pThis->mTextures, tTexture)) {
          sys::sptr<CTextureLoader> tLoader {new TTextureLoader<sys::CFile>(tSource)};
          
          tTexture = CTextureManager::load(tLoader);
        }
        
        return new ITexture{tTexture};
      }
  };

  // utils ///////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  inline uint mapsize(uint width, uint height, uint depth, uint channels, uint flags = 0) { return flags & CTexture::COMPRESSED ? (((width + 3) >> 2) * ((height + 3) >> 2) * depth * (flags & CTexture::RGBA_S3TC_DXT1 ? 8 : 16)) : (width * height * depth * channels); }
}

#endif //__cym_ctexture_hpp__
