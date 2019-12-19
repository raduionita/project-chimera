#ifndef __gll_hpp__
#define __gll_hpp__

#include <string>
#include <exception>

namespace gll {
  typedef unsigned long ulong;
  typedef unsigned int  uint;
  typedef unsigned char ubyte;
  
  namespace dds {
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
    
    enum {
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
  }
  
  enum type {
    NONE    = 0,
    LINEAR  = 1,
    FLATMAP = 2,
    CUBEMAP = 3,
    VOLUME  = 4,
  };
  
  enum format {
    LUMINANCE,
    RGB,
    RGBA,
    RGBA_S3TC_DXT1,
    RGBA_S3TC_DXT3,
    RGBA_S3TC_DXT5,
  };
  
  inline uint clamp2one(uint val) { return val < 1 ? 1 : val; } 
  
  inline uint calcmapsize(uint width, uint height, uint depth, uint components, uint format, bool compressed = true) { return compressed ? ((width + 3) >> 2) * ((height + 3) >> 2) * depth * (format == RGBA_S3TC_DXT1 ? 8 : 16) : width * height * depth * components; }
  
  struct texture {
    static texture* load(const std::string& file) {
      if (file.empty()) {
        return nullptr;
      }
      
      // @todo: check .ext
      
    }
    static void free(texture* ptex) {
      
    }
  };
  
  struct material {
    public:
      static material load(const std::string&);
  };
  
  struct model {
    public:
      static model load(const std::string&);
  };
  
  struct animation {
    public:
      static animation load(const std::string&);
  };
  
  struct shader {
    public:
      static shader load(const std::string&);
  };
  
  struct effect {
    
  };
}

#endif //__gll_hpp__
