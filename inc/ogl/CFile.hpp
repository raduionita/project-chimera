#ifndef __ogl_cfile_hpp__
#define __ogl_cfile_hpp__

#include "ogl/ogl.hpp"
#include "sys/CFile.hpp"

namespace ogl {
  class CFile : public sys::CFile {
      using sys::CFile::CFile;
  };
  
  class CDDSFile : public CFile {
      using ogl::CFile::CFile;
    private:
      struct SFormat {
        ulong size;
        ulong flags;
        ulong fourcc;
        ulong bpp;
        ulong rbitmask;
        ulong gbitmask;
        ulong bbitmask;
        ulong abitmask;
      };
      struct SHeader {
        ulong         size;
        ulong         flags;
        ulong         height;
        ulong         width;
        ulong         linearsize;
        ulong         depth;          // only if DDS_HEADER_FLAGS_VOLUME is in header_t::flags
        ulong         mipmaps;
        ulong         _unused_1_[11];
        SFormat       format; 
        ulong         caps1;
        ulong         caps2;
        ulong         _unused_2_[3];
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
    private:
      static inline uint clamp2one(uint val) { return val < 1 ? 1 : val; } 
      static inline uint mapsize(uint width, uint height, uint depth, uint components, uint format, bool compressed = true) { return compressed ? ((width + 3) >> 2) * ((height + 3) >> 2) * depth * (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT ? 8 : 16) : width * height * depth * components; }
  };
}

#endif //__ogl_cfile_hpp__
