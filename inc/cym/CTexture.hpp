#ifndef __cym_ctexture_hpp__
#define __cym_ctexture_hpp__

#include "cym/cym.hpp"
#include "cym/CObject.hpp"
#include "cym/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "sys/TSingleton.hpp"
#include "sys/CException.hpp"
#include "sys/CTask.hpp"
#include "cym/TInstance.hpp"
#include "glm/CVector.hpp"
#include "ogl/CTexture.hpp"

#include <functional>

namespace cym {
  class CTexture;           typedef sys::ptr<CTexture>       PTexture;
  class CTextureManager;
  class CTextureLoader;     typedef sys::ptr<CTextureLoader> PTextureLoader;
  template<typename T> class TTextureLoader;
  
  // resources ///////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTexture : public cym::CResource, public CObject { // or should this be CBuffer since it holds data/memory
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
// @todo: these 4 enums should be 1 enum, so u can passe it to CTextureManager::load(...,EOption::XXX)
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
    private:
      static constexpr GLenum sCubeMapTargets[6] = {GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, };
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
      CTexture(const std::string& = "");
      ~CTexture();
    public: // get/set-ers
      void          setFiltering(EFiltering eFiltering);
      void          setWrapping(EWrapping eWrapping) const;
      inline GLenum getTarget() const { return mTarget; }
      inline EType  getType() const { return mType; }
      inline GLenum getFormat() const { return mFormat; }
// @todo: remove these, can't set them after texture was created
      inline void   setType(EType eType) { mType = eType; mTarget = (eType == EType::CUBEMAP ? GL_TEXTURE_CUBE_MAP : (eType == EType::VOLUME ? GL_TEXTURE_3D : mTarget)); }
      inline void   setFormat(GLenum format) { mFormat = format; }
      inline void   setMipmaps(GLcount m) { mMipmaps = m == 0 ? 1 : m; }
      inline void   setWidth(GLsizei w)   { mWidth = w; }
      inline void   setHeight(GLsizei h)  { mHeight = h; }
      inline void   setDepth(GLsizei d)   { mDepth = d; }
// @todo: move to RenderState or something, slot is not dependent on this texture 
      inline GLint  getSlot() const { return mSlot; }
    public: // actions
      virtual GLvoid   bind(bool=true) const override;
              GLvoid   bind(GLint);
              GLvoid   sampler(CShader*);
  };
  
  inline GLbitfield operator |(const CTexture::EWrapping& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) | (GLbitfield)(rhs)); }
  inline GLbitfield operator &(const CTexture::EWrapping& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) & (GLbitfield)(rhs)); }
  inline GLbitfield operator |(const CTexture::EFiltering& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) | (GLbitfield)(rhs)); }
  inline GLbitfield operator &(const CTexture::EFiltering& lhs, const CTexture::EWrapping& rhs) { return (GLbitfield)((GLbitfield)(lhs) & (GLbitfield)(rhs)); }
  
  // int w, h;
  // int miplevel = 0;
  // glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_WIDTH, &w);
  // glGetTexLevelParameteriv(GL_TEXTURE_2D, miplevel, GL_TEXTURE_HEIGHT, &h);
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureLoader : public cym::CResourceLoader {
      friend class CTexture;
      friend class CTextureManager;
    public:
      using EFlag = CTexture::EFlag;
      enum EHint { MIPMAPS = 1 };
    public:
      sys::PStream mStream;
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
      inline CTextureLoader(const sys::string& tName) : CResourceLoader(tName) { SYS_LOG_NFO("cym::CTextureLoader::CTextureLoader(sys::string&)::" << this);  }
      inline ~CTextureLoader() { SYS_LOG_NFO("cym::CTextureLoader::~CTextureLoader()::" << this); }
    public:
      virtual inline void         load(PTexture) { throw sys::exception("CTextureLoader::load(PTexture) NOT overriden!",__FILE__,__LINE__);  };
    public:
      template<typename T> inline static sys::ptr<TTextureLoader<T>> from(const T& tSource) { return new TTextureLoader<T>{tSource}; }
      template<typename T, typename... Args> inline static sys::string name(const T& tSource, Args&&... args) { return TTextureLoader<T>::name(tSource, std::forward<Args>(args)...); }
    public:
      inline sys::PStream& getStream() { if (mStream == nullptr) { mStream = new sys::stream; } return mStream; }
  };
  
  template<typename T> class TTextureLoader : public cym::CTextureLoader { 
    public:
      using cym::CTextureLoader::CTextureLoader;
    //   typedef std::function<void(sys::ptr<TTextureLoader<T>>)> function_type;
    // protected:
    //   T             mSource;
    //   sys::string   mName;
    //   function_type mFunction;
    // public:
    //   TTextureLoader(const T& tSource, const sys::string& tName, function_type tFunction) : mSource{tSource}, mName{tName}, mFunction{tFunction} {}
    // public:
    //   inline T& getSource() const { return mSource; }
  };
  
  template<> class TTextureLoader<sys::file> : public CTextureLoader {
      friend class CTexture;
      friend class CTextureManager;
    protected:
      sys::file mFile;
    public:
      TTextureLoader(const sys::file& tFile) : CTextureLoader(name(tFile)), mFile{tFile} { };
    public:
      virtual void load(PTexture) override;
    public:
      inline static sys::string name(const sys::file& tFile) { return tFile.path(); }
    public:
      sys::file& getFile() { return mFile; }
  };
  
  template<> class TTextureLoader<cym::null> : public CTextureLoader {
      friend class CTexture;
      friend class CTextureManager;
    protected:
      cym::uint mLength {2u};
    public:
      inline TTextureLoader(const cym::null& n, const cym::uint l) : CTextureLoader(name(n, l)), mLength{l} { }
    public:
      inline static sys::string name(const cym::null&, const cym::uint l) { return std::string("null:") + sys::to_string(l) + 'x' + sys::to_string(l); }
    public:
      virtual void load(PTexture) override;
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureManager : public cym::TResourceManager<CTexture>, public sys::TSingleton<CTextureManager> {
      friend class cym::CTexture;
      friend class cym::CTextureLoader;
      friend class sys::TSingleton<cym::CTextureManager>;
    protected:
      sys::map<std::string, sys::ptr<CTexture>> mTextures;
    protected:
      CTextureManager();
      ~CTextureManager();
    public:
      inline static void boot() { CTextureManager::getSingleton(); }
      /* remeber/cache texture  */
      static void save(PTexture pTexture) {
        static auto& self {CTextureManager::getSingleton()};
        SYS_LOG_NFO("cym::CTextureManager::save(PTexture)");
        self.mTextures.insert(std::pair(pTexture->mName, pTexture));
      }
      /* load texture from texture loader */
      static PTexture load(PTextureLoader pLoader, bool bSearch=true);
      /* load PTexture using a TTextureLoader */
      template<typename T> inline static PTexture load(sys::ptr<TTextureLoader<T>> pLoader, bool bSearch = true) { return CTextureManager::load(PTextureLoader{pLoader},bSearch); }
      /* load texture routing to a texture loader // = load(sys::CFile{"path/to/texture.tex"}) */
      template<typename T, typename... Args> static PTexture load(const T& tSource, Args&&... args) {
        SYS_LOG_NFO("cym::CTextureManager::load(T&,Args&&)");
        // manager
        static auto& self {cym::CTextureManager::getSingleton()};
        // container resource
        PTexture pTexture;
        // name of the resource
        const sys::string& tName {CTextureLoader::name(tSource,std::forward<Args>(args)...)};
        // search for it first
        if (!sys::find(tName, self.mTextures, pTexture)) {
          PTextureLoader tLoader{new TTextureLoader<T>{tSource, std::forward<Args>(args)...}};
          // this will return an empty geometry imediatly, and async load its data (meshs,materials,textures,vbos)
          pTexture = CTextureManager::load(tLoader, false);
        }
        // return copy of 
        return {new CTexture{*pTexture}};
      }
  };
  
// @todo: move this inside cym.hpp  
  inline uint mapsize(uint width, uint height, uint depth, uint channels, uint flags = 0) { return flags & CTexture::COMPRESSED ? (((width + 3) >> 2) * ((height + 3) >> 2) * depth * (flags & CTexture::RGBA_S3TC_DXT1 ? 8 : 16)) : (width * height * depth * channels); }
}

#endif //__cym_ctexture_hpp__
