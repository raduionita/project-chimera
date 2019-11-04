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
    
  struct resource {
  
  };
  
  struct texture : public resource {
    public:
      struct mipmap {
        uint   width  {0};
        uint   height {0};
        uint   depth  {0};
        uint   size   {0};
        ubyte* data   {nullptr};
      };
      struct layer {
        std::vector<mipmap*> mipmaps;
      };
    public:
      uint width          {0};
      uint height         {0};
      uint depth          {0};
      uint mipmaps        {1};
      uint bpp            {0};
      std::vector<layer*> layers;
      int  type           {FLATMAP};
      uint components     {0}; 
      bool compressed     {false};
      uint format         {RGBA};
      uint alinment       {1};
    public:
      static bool load(texture* ptex, const std::string& file) {
        if (file.empty()) {
          // @todo: warn
          return false;
        }
        
        // @todo: check .ext
        
        return loaddds(ptex, file);
      }
      static void free(texture* ptex) {
        for (auto& plyr : ptex->layers) {
          for (auto& pmip : plyr->mipmaps) {
            delete [] pmip;
          }
          delete plyr;
        }
      }
    private:
      static bool loaddds(texture* ptex, const std::string& file) {
        FILE* fptr = NULL;
        fptr = ::fopen(file.c_str(), "rb");
        
        if (fptr == NULL) {
          // @todo: warn
          return false;
        }
        
        char ftyp[3];
        ::fread(ftyp, 1, 4, fptr);
        if (::strncmp(ftyp, "DDS", 4) != 0) {
          ::fclose(fptr);
          // @todo: warn
          return false;
        }
        
        dds::header_t head;
        ::fread(&head, sizeof(dds::header_t), 1, fptr);
        
        
        if ((head.caps2 & dds::CUBEMAP)) {
          ptex->type = CUBEMAP;
        } else if ((head.caps2 & dds::VOLUME) && (head.depth > 0)) {
          ptex->type = VOLUME;
        }
  
        ptex->components = (head.pf.fourcc == dds::FOURCC) || (head.pf.bpp == 24) ? 3 : 4;
        
        if (head.pf.flags & dds::FOURCC) {
          switch (head.pf.fourcc) {
            case dds::FOURCC_DTX1: ptex->format = RGBA_S3TC_DXT1;
            case dds::FOURCC_DTX3: ptex->format = RGBA_S3TC_DXT3;
            case dds::FOURCC_DTX5: ptex->format = RGBA_S3TC_DXT5;
            default:
              ::fclose(fptr);
              // @todo: warn
              return false;
          }
          ptex->compressed = true;
        } else if (head.pf.flags == dds::RGBA && head.pf.bpp == 32) {
          ptex->format = RGBA;
        } else if (head.pf.flags == dds::RGB && head.pf.bpp == 32) {
          ptex->format = RGBA;
        } else if (head.pf.flags == dds::RGB && head.pf.bpp == 24) {
          ptex->format = RGB;
        } else if (head.pf.bpp == 8) {
          // @todo: luminance // otex->components = 1
          ::fclose(fptr);
          return false;
        } else {
          ::fclose(fptr);
          // @todo: warn
          return false;
        }
  
        ptex->bpp    = head.pf.bpp;
        ptex->width  = clamp2one(head.width);
        ptex->height = clamp2one(head.height);
        ptex->depth  = head.depth;
        ptex->layers.resize(ptex->type = CUBEMAP ? 6 : 1);
        ptex->mipmaps = head.mipmaps == 0 ? 1 : head.mipmaps;
        
        uint width  = 0;
        uint height = 0;
        uint depth  = 0;
        uint layers = ptex->layers.size();
      
        for (uint i = 0; i < layers; i++) {
          layer* plyr {new layer};
          
          width  = head.width;
          height = head.height;
          depth  = head.depth ? head.depth : 1;
          
          plyr->mipmaps.resize(head.mipmaps);
          
          for (uint j = 0; (j < head.mipmaps) && (width || height); j++) {
            mipmap* pmip {new mipmap};
            pmip->width = width;
            pmip->width = height;
            pmip->width = depth;
            
            pmip->size = calcmapsize(width, height, depth, ptex->components, ptex->format, ptex->compressed);
            pmip->data = new ubyte[pmip->size];
            
            plyr->mipmaps[j] = pmip;
            
            width  = clamp2one(width  >> 1);
            height = clamp2one(height >> 1);
            depth  = clamp2one(depth  >> 1);
          }
          
          ptex->layers[i] = plyr;
        }
        
        return true;
      }
      static void loadtga(texture* ptex, const std::string* file) {
        
      }
  };
  
  struct material : public resource {
    public:
      static material load(const std::string&);
  };
  
  struct model : public resource {
    public:
      static model load(const std::string&);
  };
  
  struct animation : public resource {
    public:
      static animation load(const std::string&);
  };
  
  struct shader : public resource {
    public:
      static shader load(const std::string&);
  };
}

#endif //__gll_hpp__
