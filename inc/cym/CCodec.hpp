#ifndef __cym_ccodec_hpp__
#define __cym_ccodec_hpp__

#include "glm/CVector.hpp"
#include "cym/cym.hpp"
#include "sys/CException.hpp"
#include "sys/CStream.hpp"
#include "cym/CModel.hpp"

namespace cym {
  class CCodec;        typedef sys::TPointer<CCodec> PCodec; 
  class CResourceInfo; typedef sys::TPointer<CResourceInfo> PResourceData;
  
  class CCodec {
    public:
      virtual ~CCodec() { log::nfo << "cym::CCodec::CCodec()::" << this << log::end; }
    public:
      virtual sys::CString  type() { throw sys::CException("NOT IMPLEMENTED",__FILE__,__LINE__); }
      virtual PResourceData decode(const sys::CFile&) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
      virtual void decode(CResourceInfo&) { throw sys::CException("NOT IMPLEMENTED", __FILE__, __LINE__); }
  };
  
  // textures ////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CTextureCodec : public CCodec { };

  class CDDSCodec : public CTextureCodec {
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
      ~CDDSCodec() { log::nfo << "cym::CDDSCodec::~CDDSCodec()::" << this << log::end; }
    public:
      virtual inline sys::CString type() override { return "dds"; }
      virtual PResourceData decode(const sys::CFile&) override;
  };
  
  class CTGACodec : public CTextureCodec {
      
  };
  
  // models //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  class CModelCodec : public CCodec {
      
  };
  
  class COBJCodec : public CModelCodec {
    protected:
      struct index_t {
        unsigned int position;
        unsigned int texcoord;
        unsigned int normal;
        index_t() : position(0), texcoord(0), normal(0) { };
        index_t(unsigned int a) : position(a), texcoord(a), normal(a) { };
        index_t(unsigned int a, unsigned int b, unsigned int c) : position(a), texcoord(b), normal(c) { };
      };
      
      friend inline bool operator <(const index_t& lhs, const index_t& rhs);
    
      using face_t    = sys::CVector<index_t>;
      using vec2_t    = glm::vec2;
      using vec3_t    = glm::vec3;
      using color_t   = glm::vec3;
      
      using unknown_t = sys::map<sys::CString, sys::CString>;
      
      struct channel_t {
        color_t     color;
        sys::string texture;
        channel_t()                       : color(0.f), texture("") { }
        channel_t(float c)                : color(c),   texture("") { }
        channel_t(float c, const char* t) : color(c),   texture(t)  { }
      };
      
      struct material_t {
        // fields: name
        std::string name;
        // fields: channels
        channel_t   ambient;
        channel_t   diffuse;
        channel_t   normal;
        channel_t   specular;
        channel_t   transmission;
        channel_t   emission;
        // fields: other
        float       shininess = {1.f};           // shininess
        float       ior       = {1.f};           // index of refractions
        // fields: unknown
        unknown_t   unknown;     // unknown parameters
      };
    
      struct mesh_t {
        sys::block<float> vertices;
        sys::block<uint>  indices; 
        material_t        material;   
      };
    public:
      ~COBJCodec() { log::nfo << "cym::COBJCodec::~COBJCodec()::" << this << log::end; }
    public:
      virtual inline sys::string type() override { return "obj"; }
      virtual void               decode(cym::CResourceInfo&) override;
    protected:
      static void _mesh(sys::block<mesh_t>& tMeshes, const sys::block<vec3_t>& tPositions, const sys::block<vec2_t>& tTexcoords, const sys::block<vec3_t>& tNormals, const sys::block<index_t>& tIndices, const material_t& material, const sys::string& tName);
      static void _material(const sys::string& file, sys::map<sys::string,material_t>& materials, bool& tDone);
  };
  
  class CMD5Codec : public CModelCodec {
    public: 
      virtual inline sys::CString type() override { return "md5"; }
      virtual PResourceData decode(const sys::CFile&) override;
  };
}

#endif //__cym_ccodec_hpp__
