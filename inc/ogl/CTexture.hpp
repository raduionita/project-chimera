#ifndef __ogl_ctexture_hpp__
#define __ogl_ctexture_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CObject.hpp"
#include "ogl/CResource.hpp"
#include "sys/CFile.hpp"
#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace ogl {
  class CTexture;             typedef sys::CPointer<CTexture>            PTexture; 
  class CTextureManager;      typedef sys::CPointer<CTextureManager>     PTextureManager;
  class CTextureLoader;       typedef sys::CPointer<CTextureLoader>      PTextureLoader;
  class CTextureStream;       typedef sys::CPointer<CTextureStream>      PTextureStream;
  class CFileTextureBuilder;  typedef sys::CPointer<CFileTextureBuilder> PFileTextureBuilder;
  
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
      CTexture(PTextureStream);
      CTexture(GLenum target);
      CTexture(EType type);
      ~CTexture();
    public: // actions
      virtual GLvoid bind(bool=true) const override;
              GLvoid bind(GLuint);
      GLvoid         sampler(CShader*);
      virtual void   load(PTextureStream) final;
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
  
  class CTextureStream : public CResourceStream {
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
    public:
      CTextureStream() = default;
      CTextureStream(const sys::CVector<float>& data) { }
  };
  
  class CTextureLoader : public CResourceLoader {
      using ogl::CResourceLoader::CResourceLoader;
    public:
      static PTextureStream load(const sys::CString& file);
    public:
      virtual PTextureStream from(const sys::CString& file) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
  };
  
  template <typename T> class CTextureBuilder : public CResourceBuilder {
      using CResourceBuilder::CResourceBuilder;
    public:
      virtual PTextureStream from(const T& file) = 0;
  };
  
  class CTextureManager : public CResourceManager, public sys::CSingleton<CTextureManager> {
    public:
      CTextureManager();
      ~CTextureManager();
    public:
      static PTexture load(const sys::CString& name);
      
      template <typename T> static PTexture load(const T& that, const sys::CString& name = "") {
        static PTextureManager& self = CTextureManager::instance();
        log::nfo << "ogl::CTextureManager::load(T&,sys::CString&)::" << self << " NAME:" << name << log::end;
// @todo: search for texture in cache
        CTextureBuilder<T> pUsing {nullptr};
        for (auto& pBuilder : self->builders()) {
          if ((pUsing = sys::dynamic_pointer_cast<CTextureBuilder<T>>(pBuilder))) {
            pUsing->from(that);
            
// @todo: put texture in cache
          }
        }
// @todo: return null texture (stream) from cache if can't build texture
      }
  };
  
  class CFileTextureBuilder : public CTextureBuilder<sys::CFile> {
      using CTextureBuilder::CTextureBuilder;
    protected:
      sys::CVector<PTextureLoader> mLoaders;
    public:
      CFileTextureBuilder();
    public: // type
      virtual inline sys::CString type() const override { return "file"; }
    public: // loaders
      template <typename T, class = typename std::enable_if<std::is_base_of<ogl::CTextureLoader,T>::value>::type> const T* loader(T* pLoader) {
        // move loader to list of loaders
        mLoaders.push_back(pLoader);
        // return inserted
        return mLoaders.back().ptr();
      }
      inline sys::CVector<PTextureLoader>::value_type loader(const sys::CString& name) { 
        for (auto& pLoader : mLoaders) {
          if (pLoader->able(name)) {
            return pLoader;
          }
        }
        throw sys::CException("Missing CTextureLoader for '"+ name +"'", __FILE__, __LINE__);
      }
      inline const sys::CVector<PTextureLoader>& loaders() const { return mLoaders; }
    public: // build
      PTextureStream from(const sys::CFile& file);
  };
  
  class CDDSTextureLoader : public CTextureLoader {
      using ogl::CTextureLoader::CTextureLoader;
    public:
      virtual inline bool    able(const std::any& that) const {
        try {
          auto file = std::any_cast<std::string>(that);
          return 0 == file.substr(file.find_first_of(".")+1).compare("dds");
        } catch (const std::bad_any_cast& e) {
          throw sys::CException(e.what(), __FILE__, __LINE__);
        }
      }
      virtual PTextureStream from(const sys::CString& file);
  };
  
  class CTGATextureLoader : public CTextureLoader {
      using ogl::CTextureLoader::CTextureLoader;
    public:
      virtual inline bool    able(const std::any& that) const {
        try {
          auto file = std::any_cast<std::string>(that);
          return 0 == file.substr(file.find_first_of(".")+1).compare("tga");
        } catch (const std::bad_any_cast& e) {
          throw sys::CException(e.what(), __FILE__, __LINE__);
        }
      }
      virtual PTextureStream load(const sys::CString& file) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
  };
}

#endif //__ogl_ctexture_hpp__
