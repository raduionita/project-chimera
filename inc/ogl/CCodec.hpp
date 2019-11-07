#ifndef __ogl_ccodec_hpp__
#define __ogl_ccodec_hpp__

#include "ogl/ogl.hpp"
#include "sys/CFile.hpp"
#include "sys/CSingleton.hpp"

namespace ogl {
  class CCodec {
    public:
      virtual void        decode(const sys::CFile&) const = 0;
      virtual const char* type() const = 0;
      virtual bool        able(const sys::CFile& file) const { return ::strcmp(file.extension(), type()) == 0; }
  };
  
  class CTextureCodec : CCodec {
      using CCodec::CCodec;
  };
  
  class CDDSCodec : public CTextureCodec {
      using CTextureCodec::CTextureCodec;
    private:
      struct SCaps {
        uint caps1;
        uint caps2;
        uint caps3;
        uint caps4;
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
        uint         size;
        uint         flags;
        uint         height;
        uint         width;
        uint         linearsize;
        uint         depth;          // only if DDS_HEADER_FLAGS_VOLUME is in header_t::flags
        uint         mipmaps;
        uint         _unused_1_[11];
        SFormat       format; 
        SCaps         caps;
        uint         _unused_2_;
      };
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
      virtual inline const char* type() const override { return "dds"; }
      virtual void decode(const sys::CFile&) const override;
    private:
      static inline uint clamp2one(uint val) { return val < 1 ? 1 : val; } 
      static inline uint mapsize(uint width, uint height, uint depth, uint components, uint format, bool compressed = true) { return compressed ? ((width + 3) >> 2) * ((height + 3) >> 2) * depth * (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16) : width * height * depth * components; }
  };
  
  class CTGACodec : public CCodec {
      
  };
  
  class CCodecManager : public sys::CSingleton<CCodecManager> {
      friend class CTextureManager;
    protected:
      sys::CMap<sys::CString, CCodec*> mCodecs;
    public:
      CCodec* codec(const sys::CString& ext) { return mCodecs[ext]; }
  };
}

#endif //__ogl_ccodec_hpp__
