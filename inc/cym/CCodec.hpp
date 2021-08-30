#ifndef __cym_ccodec_hpp__
#define __cym_ccodec_hpp__

#include "sys/CException.hpp"
#include "sys/CStream.hpp"
#include "cym/cym.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CScene.hpp"
#include "cym/TManager.hpp"
#include "glm/CVector.hpp"

namespace cym {
  class CCodec; typedef sys::ptr<CCodec> PCodec;
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  enum class ECodec : uint { EXT = 0, DDS, TGA, BMP, PNG, JPG, KTX, DAE, OBJ, MD5, FBX, SCENE };
  
  class CCodec {
    public:
      virtual ~CCodec() { SYS_LOG_NFO("cym::CCodec::~CCodec()::" << this); }
    public:
      virtual const std::string& getType() const { throw sys::exception("CCodec::getType() NOT OVERRIDEN", __FILE__, __LINE__); }
      virtual void decode(PResourceLoader) { throw sys::exception("CCodec::decode(PResourceLoader) NOT OVERRIDEN", __FILE__, __LINE__); }
  };
  
  template<typename T, ECodec C> class TCodec : public CCodec { };
  
  class CTextureCodec : public CCodec { 
    private:
      std::string mType;
    public:
      inline CTextureCodec(const std::string& tType) : mType{tType} { SYS_LOG_NFO("cym::CTextureCodec::CTextureCodec(std::string&)::"); }
    public:
      virtual inline const sys::string& getType() const override { return mType; }
      virtual void decode(PResourceLoader) override { throw sys::exception("CTextureCodec::decode(PResourceLoader) NOT OVERRIDEN", __FILE__, __LINE__); }
  };
  
  class CGeometryCodec : public CCodec {
    private:
      std::string mType;
    public:
      inline CGeometryCodec(const std::string& tType) : mType{tType} { SYS_LOG_NFO("cym::CGeometryCodec::CGeometryCodec(std::string&)::"); }
    public:
      virtual inline const sys::string& getType() const override { return mType; }
      virtual void decode(PResourceLoader) override { throw sys::exception("CGeometryCodec::decode(PResourceLoader) NOT OVERRIDEN", __FILE__, __LINE__); }
  };  
  
  class CSceneCodec : public CCodec {
    private:
      std::string mType;
    public:
      inline CSceneCodec(const std::string& tType) : mType{tType} { SYS_LOG_NFO("cym::CSceneCodec::CSceneCodec(std::string&)::"); }
    public:
      virtual inline const sys::string& getType() const override { return mType; }
      virtual void decode(PResourceLoader) override { throw sys::exception("CSceneCodec::decode(PResourceLoader) NOT OVERRIDEN", __FILE__, __LINE__); }
  };
    
  // textures ////////////////////////////////////////////////////////////////////////////////////////////////////////

  template<> class TCodec<CTexture,ECodec::DDS> : public CTextureCodec {
    private:
      enum {
        DDS_CAPS              = 0x00000001,
        DDS_HEIGHT            = 0x00000002,
        DDS_WIDTH             = 0x00000004,
        DDS_PITCH             = 0x00000008,
        DDS_PIXELFORMAT       = 0x00001000,
        DDS_MIPMAPCOUNT       = 0x00020000,
        DDS_LINEARSIZE        = 0x00080000,
        DDS_DEPTH             = 0x00800000,
        // pixel format flags
        DDS_ALPHAPIXELS       = 0x00000001,
        DDS_FOURCC            = 0x00000004,
        DDS_RGB               = 0x00000040,
        DDS_RGBA              = 0x00000041,
        // caps1 flags
        DDS_COMPLEX           = 0x00000008,
        DDS_TEXTURE           = 0x00001000,
        DDS_MIPMAP            = 0x00400000,
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
        DDS_FOURCC_DTX1       = 0x31545844, // = DTX1(in ASCII)
        DDS_FOURCC_DTX3       = 0x33545844, // = DTX3(in ASCII)
        DDS_FOURCC_DTX5       = 0x35545844, // = DTX5(in ASCII)
      };
      struct SFormat {
        uint size;
        uint flags;
        uint fourcc;
        uint bpp;
        uint rbitmask;
        uint gbitmask;
        uint bbitmask;
        uint abitmask;
      };
      struct SHeader {
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
      struct SDXTColBlock {
        ushort col0;
        ushort col1;
        utiny  row[4];
      };
      struct SDXT3AlphaBlock {
        ushort row[4];
      };
      struct SDXT5AlphaBlock {
        utiny alpha0;
        utiny alpha1;
        utiny row[6];
      };
    public:
      inline TCodec() : CTextureCodec("dds") { SYS_LOG_NFO("cym::TCodec<CTexture,DDS>::TCodec()::" << this); }
      inline ~TCodec() { SYS_LOG_NFO("cym::TCodec<CTexture,DDS>::~TCodec()::" << this); }
    public:
      virtual void decode(PResourceLoader) override;
  };
  
  template<> class TCodec<CTexture,ECodec::TGA> : public CTextureCodec {
      union pixel { sys::uint rgba; struct { sys::ubyte r, g, b, a; }; };
    public:
      inline TCodec() : CTextureCodec("tga") { SYS_LOG_NFO("cym::TCodec<CTexture,TGA>::TCodec()::" << this); }
      inline ~TCodec() { SYS_LOG_NFO("cym::TCodec<CTexture,TGA>::~TCodec()::" << this); }
    public:
      virtual void decode(PResourceLoader) override;
  };
  
  template<> class TCodec<CTexture,ECodec::BMP> : public CTextureCodec {
      union pixel { sys::uint bgra; struct { sys::ubyte b, g, r, a; }; };
      enum {
        INFO_BMP   = 0,
        INFO_BMP_0 = 0,
        INFO_BMP_1 = 1,
        INFO_BMP_2 = 2,
        INFO_BBP   = 28,
      };
    public:
      inline TCodec() : CTextureCodec("bmp") { SYS_LOG_NFO("cym::TCodec<CTexture,BMP>::TCodec()::" << this); }
      inline ~TCodec() { SYS_LOG_NFO("cym::TCodec<CTexture,BMP>::~TCodec()::" << this); }
    public:
      virtual void decode(PResourceLoader) override;
  };
  
  template<> class TCodec<CTexture,ECodec::PNG> : public CTextureCodec { };
  template<> class TCodec<CTexture,ECodec::JPG> : public CTextureCodec { };
  template<> class TCodec<CTexture,ECodec::KTX> : public CTextureCodec { };
  
  // models //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<> class TCodec<CGeometry,ECodec::OBJ> : public CGeometryCodec {
    public:
      typedef CGeometry resource_type;
      static constexpr ECodec kType {ECodec::OBJ};
    protected:
      // index
      struct SIndex {
        int position;
        int texcoord;
        int normal;
        SIndex() : position(-1), texcoord(-1), normal(-1) { };
        SIndex(int a) : position(a), texcoord(a), normal(a) { };
        SIndex(int a, int b, int c) : position(a), texcoord(b), normal(c) { };
      };
      // data
      struct SData {
        sys::block<glm::vec3>  positions;
        sys::block<glm::vec2>  texcoords;
        sys::block<glm::vec3>  normals;
        sys::block<glm::uint>  indices;
      };
    // fiends
      friend inline bool operator <(const SIndex& lhs, const SIndex& rhs);
    public:
      inline TCodec() : CGeometryCodec("obj") { SYS_LOG_NFO("cym::TCodec<CGeometry,OBJ>::~TCodec()::" << this); }
      inline ~TCodec() { SYS_LOG_NFO("cym::TCodec<CGeometry,OBJ>::~TCodec()::" << this); }
    public:
      virtual void decode(PResourceLoader) override;
    protected:
      static void  decodeMaterial(const sys::string& tFile, sys::map<sys::string, PMaterialLoader>& tMaterialLoaders, bool& tDone);
  };
  
  template<> class TCodec<CGeometry,ECodec::DAE> : public CGeometryCodec {
      using EOption = CGeometryLoader::EFlag;
    public:
      inline TCodec() : CGeometryCodec("dae") { SYS_LOG_NFO("cym::TCodec<CGeometry,DAE>::~TCodec()::" << this); }
      inline ~TCodec() { SYS_LOG_NFO("cym::TCodec<CGeometry,DAE>::~TCodec()::" << this); }
    public:
      virtual void decode(PResourceLoader) override;
  };
  
  template<> class TCodec<CGeometry,ECodec::MD5> : public CGeometryCodec { };
  template<> class TCodec<CGeometry,ECodec::FBX> : public CGeometryCodec { };
  
  template<> class TCodec<CScene,ECodec::SCENE> : public CSceneCodec {
      using EOption = CGeometryLoader::EFlag;
    public:
      inline TCodec() : CSceneCodec("scene") { SYS_LOG_NFO("cym::TCodec<CScene,SCENE>::~TCodec()::" << this); }
      inline ~TCodec() { SYS_LOG_NFO("cym::TCodec<CScene,SCENE>::~TCodec()::" << this); }
    public:
      virtual void decode(PResourceLoader) override;
  };
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
// @todo: refactor codec manager so it supports same file type on different resources (ex: texture.xml & model.xml) 
  
  class CCodecManager : public cym::TManager<CCodec>, public sys::TSingleton<CCodecManager> {
      friend class sys::TSingleton<CCodecManager>;
    protected:
      std::map<std::string,PCodec> mCodecs;
    protected:
      CCodecManager();
      ~CCodecManager();
    public:
      inline static void boot() { CCodecManager::getSingleton(); }
    public:
      /* */
      static void    addCodec(PCodec&& pCodec);
      /* */
      static PCodec& getCodec(const std::string& ext);
  };
}

#endif //__cym_ccodec_hpp__
