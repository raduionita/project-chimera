#include "cym/CTexture.hpp"
#include "cym/CShader.hpp"
#include "cym/CException.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  CTexture::CTexture(const std::string& tName) : cym::CResource(tName) {
    SYS_LOG_NFO("cym::CTexture::CTexture()::" << this);
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::CTexture(sys::spo<CTextureLoader> rLoader) {
    SYS_LOG_NFO("cym::CTexture::CTexture(sys::spo<CTextureLoader>)::" << this);
    load(rLoader);
  }
  
  CTexture::~CTexture() {
    SYS_LOG_NFO("cym::CTexture::~CTexture()::" << this << " NAME:" << mName);
    if (!isInstance()) {
      GLCALL(::glDeleteTextures(1, &mID));
      GLCALL(::glBindTexture(mTarget, 0));
    }
  }
  
  void CTexture::load(sys::spo<CTextureLoader> rLoader) {
    SYS_LOG_NFO("cym::CTexture::load(sys::spo<CTextureLoader>)::" << this);
    
    static GLenum targets[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,};
    
    uint   faces    = rLoader->flags & EFlag::CUBEMAP ? 6 : 1;
    uint   channels = rLoader->bpp == 24 ? 3 : 4;
    uint   width    = 0;
    uint   height   = 0;
    uint   depth    = 0;
    uint   size     = 0;
    uint&  mipmaps  = rLoader->mipmaps;
    uint   flags    = rLoader->flags | EFlag::MIPMAPED;
    byte*  stream   = rLoader->mStream->ptr();
    
    mTarget   = (flags & EFlag::CUBEMAP) ? GL_TEXTURE_CUBE_MAP : (flags & EFlag::VOLUME) ? GL_TEXTURE_3D : GL_TEXTURE_2D;
    
    mInternal = flags & EFlag::RGBA_S3TC_DXT1 ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : 
                flags & EFlag::RGBA_S3TC_DXT3 ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT : 
                flags & EFlag::RGBA_S3TC_DXT5 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : 
                flags & EFlag::RGBA           ? GL_RGBA : 
                flags & EFlag::RGB            ? GL_RGB : GL_LUMINANCE;
    
    mFormat  = flags & EFlag::BGRA ? GL_BGRA :
               flags & EFlag::BGR  ? GL_BGR  : 
               flags & EFlag::RGBA ? GL_RGBA :
               flags & EFlag::RGB  ? GL_RGB  : GL_RED; // GL_RED, GL_RG, GL_RGB,...
    
    GLenum type = GL_UNSIGNED_BYTE;
    
    GLCALL(::glGenTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, mID));
    GLCALL(::glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
        
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_BASE_LEVEL, 0));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAX_LEVEL, mipmaps));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    
// @todo: this might not be good for all formats

    for (uint i = 0; i < faces; i++) {
      if(faces > 1) mTarget = targets[i];
      width  = rLoader->width;
      height = rLoader->height;
      depth  = rLoader->depth;
      for (ushort j = 0; j < mipmaps && (width || height); j++) {
        size  = cym::mapsize(width, height, depth, channels, flags);
        if (flags & EFlag::COMPRESSED) {
          if (flags & EFlag::VOLUME) {
            GLCALL(::glCompressedTexImage3D(mTarget, j, mInternal, width, height, depth, 0, size, stream));
          } else {
            GLCALL(::glCompressedTexImage2D(mTarget, j, mInternal, width, height, 0, size, stream));
          }
        } else {
          if (flags & EFlag::VOLUME) {
            GLCALL(::glTexImage3D(mTarget, j, mInternal, width, height, depth, 0, mFormat, type, stream));
          } else {
            GLCALL(::glTexImage2D(mTarget, j, mInternal, width, height, 0, mFormat, type, stream));
          }
        }
        stream += size;
      }
    }
    
    if (mipmaps <= 1 && flags & EFlag::MIPMAPED) {
      GLCALL(::glGenerateMipmap(mTarget));
    }
  }
  
  GLvoid CTexture::bind(bool state/*=true*/) const {
    if (state) {
      GLCALL(::glActiveTexture(GL_TEXTURE0 + mSlot));
      GLCALL(::glBindTexture(mTarget, mID));
    } else {
      GLCALL(::glActiveTexture(GL_TEXTURE0));
      GLCALL(::glBindTexture(mTarget, 0));
    }
  }
  
  GLvoid CTexture::bind(GLint slot) {
    GLCALL(::glActiveTexture(GL_TEXTURE0 + (mSlot = slot)));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  GLvoid CTexture::sampler(cym::CShader*) {
    throw CException("NOT IMPLEMENTED");
  }
  
  void CTexture::setFiltering(cym::CTexture::EFiltering eFiltering) {
    GLCALL(::glBindTexture(mTarget, mID));
    switch(eFiltering) {
      case EFiltering::NEAREST:
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
          // sys::info << " > INFO: NEAREST" << sys::endl;
      break;
      default:
      case EFiltering::BILINEAR:
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        // sys::info << " > INFO: BILINEAR" << sys::endl;
      break;
      case EFiltering::TRILINEAR:
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
        // sys::info << " > INFO: TRILINEAR" << sys::endl;
      break;
      case EFiltering::ANISOTROPIC:
        // sys::info << " > INFO: ANISOTROPIC" << sys::endl;
      break;
    }
  }
  
  void CTexture::setWrapping(cym::CTexture::EWrapping eWrapping) const {
    GLCALL(::glBindTexture(mTarget, mID));
      
    GLenum wrapping = GL_NONE;
    if (eWrapping & EWrapping::CLAMP_TO_EDGE)
      wrapping = GL_CLAMP_TO_EDGE;
    else if (eWrapping & EWrapping::CLAMP_TO_BORDER)
      wrapping = GL_CLAMP_TO_BORDER;
    else if (eWrapping & EWrapping::REPEAT)
      wrapping = GL_REPEAT;
      
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, wrapping));
    if (mHeight > 1 || mTarget == GL_TEXTURE_2D || mTarget == GL_TEXTURE_1D_ARRAY)
      GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, wrapping));
    if (mDepth > 1 || mTarget == GL_TEXTURE_3D || mTarget == GL_TEXTURE_CUBE_MAP || mTarget == GL_TEXTURE_2D_ARRAY)
      GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, wrapping));
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { 
    SYS_LOG_NFO("cym::CTextureManager::CTextureManager()::" << this); 
  }
  
  CTextureManager::~CTextureManager() { 
    SYS_LOG_NFO("cym::CTextureManager::~CTextureManager()::" << this); 
    //mTextures.clear(); 
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TTextureLoader<sys::file>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TTextureLoader<sys::file>::load(sys::spo<CResourceLoader>)::" << this);
    
    auto pCodec = cym::CCodecManager::getCodec(mFile.ext());
    
    pCodec->decode(pResourceLoader);
  }
  
  void TTextureLoader<cym::null>::load(sys::spo<CResourceLoader> pResourceLoader) {
    SYS_LOG_NFO("cym::TTextureLoader<cym::null>::load(sys::spo<CResourceLoader>)::" << this);
    
    auto  pTextureLoader          = sys::static_pointer_cast<TTextureLoader<cym::null>>(pResourceLoader);
    sys::spo<sys::stream> tStream = pTextureLoader->getStream();
    
    const auto&     tLength = pTextureLoader->mLength; // width & height
    const auto      tLast   = tLength-1;
    // https://www.ibm.com/docs/en/aix/7.2?topic=adapters-ascii-decimal-hexadecimal-octal-binary-conversion-table
           const cym::uint tLineMaxSum   = tLength - 1;
    static const cym::uint kBpp          = 3u;
    static const cym::byte k255000255[3] {'\377', '\000', '\377'}; // FF 00 FF // 255 000 255 // purple
    static const cym::byte k128000128[3] {'\200', '\000', '\200'}; // 80 00 80 // 128 000 128 // somewhere in between
    static const cym::byte k000000000[3] {'\000', '\000', '\000'}; // 00 00 00 // 000 000 000 // black
    const cym::byte*       tColor;
    
    cym::uint r {0u}, ro {0u}, c{0u}, co {0u}, po {0u}, rc {0};
    
    const cym::uint tOffset = tLength * kBpp;
    const cym::uint tSize   = pTextureLoader->size = tLength * tLength * kBpp/* + 1*/;
    cym::byte* tBytes       = tStream->data(pTextureLoader->size);
             //tBytes[tSize-1] = '\0';
    
    for (r = 0; r < tLength; r++) {
      ro = r * tLength * kBpp; // * tOffset
      for (c = 0; c < tLength; c++) {
        co = c * kBpp;
        po = ro + co;
        rc = r + c;
        
        tColor = r == 0 || r == tLast || c == 0 || c == tLast || rc == tLineMaxSum ? &k255000255[0] : &k128000128[0];
        // rc < tLineMaxSum ? &k255000255[0] : (rc == tLineMaxSum ? &k000000000[0] : &k128000128[0]);
        
        tBytes[po + 0] = tColor[0];
        tBytes[po + 1] = tColor[1];
        tBytes[po + 2] = tColor[2];
      }
    }
    
    pTextureLoader->flags  |= CTexture::EFlag::PLANEMAP;
    pTextureLoader->flags  |= CTexture::EFlag::RGB;
    pTextureLoader->bpp     = kBpp;
    pTextureLoader->width   = tLength;
    pTextureLoader->height  = tLength;
    pTextureLoader->depth   = 1u;
    pTextureLoader->mipmaps = 1u;
  
    // null texture loader...
    //       ubyte* data = new ubyte[256 * 256 * 3 + 1];
    //       memcpy(data, notfound.data, 256 * 256 * 3 + 1);
    //       CTexture* pTexture = new CTexture(CTextureData(data, GL_RGB32F, GL_UNSIGNED_BYTE), notfound.width, notfound.height, GL_RGB, GL_TEXTURE_2D);
    //       glGenerateMipmap(GL_TEXTURE_2D);
    //       glExitIfError();
    //       delete data;
    //       return pTexture;
    // 
    //      static const struct {
    //        uint  width;
    //        uint  height;
    //        uint  bpp; /* 2:RGB16, 3:RGB, 4:RGBA */ 
    //        ubyte data[2 * 2 * 3 + 1]; // width * height * bpp + 1(null?) = 12+1
    //      } notfound = {                                          // 00 (purple) 01 (mid)
    //        2, 2, 3,                                              // 10 (mid)    11 (black)
    //        "\377\000\377\200\000\200\200\000\200\004\004\004",   //
    //        // \377\000\377 = [0][0]                              // 00 01 02 03 (l = 4)
    //        // \200\000\200 = [0][1]                              // 10 11 12 13
    //        // \200\000\200 = [1][0]                              // 20 21 22 23
    //        // \004\004\004 = [1][1]                              // 30 31 32 33
//      };
  }
}
