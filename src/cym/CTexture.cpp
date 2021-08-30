#include "cym/CTexture.hpp"
#include "cym/CShader.hpp"
#include "cym/CException.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  // texture /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTexture::CTexture(const std::string& tName) : cym::CResource(tName) {
    SYS_LOG_NFO("cym::CTexture::CTexture()::" << this);
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::~CTexture() {
    SYS_LOG_NFO("cym::CTexture::~CTexture()::" << this << " NAME:" << mName);
    if (!isInstance()) {
      GLCALL(::glDeleteTextures(1, &mID));
      GLCALL(::glBindTexture(mTarget, 0));
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
    SYS_LOG_NFO("cym::CTextureManager::CTextureManager()"); 
  }
  
  CTextureManager::~CTextureManager() { 
    SYS_LOG_NFO("cym::CTextureManager::~CTextureManager()"); 
    //mTextures.clear(); 
  }
  
  PTexture CTextureManager::load(PTextureLoader pLoader, bool bSearch/*=true*/) {
    SYS_LOG_NFO("cym::CTextureManager::load(PTextureLoader)");
    // manager
    static auto& self {cym::CTextureManager::getSingleton()};
        
// @TODO (for all resources) return a clone/copy of the texture (resource)
    
// @TODO implement bSearch
    
    // process CTextureLoader into CTexture 
    if (pLoader) {
      // load texture
      PTexture    pTexture; 
      const auto& tName {pLoader->getName()};
      // new texture
      pTexture = new CTexture{tName};
      // save texture
      CTextureManager::save(pTexture);
      // async
      sys::task([pTexture, pLoader]() mutable {
        SYS_LOG_NFO("cym::CTextureManager::load(PTextureLoader)::task");
        // load loader
        pLoader->load(pTexture);
        // computed flags
        uint   flags    = pLoader->flags | CTexture::EFlag::MIPMAPED; // @TODO forced here, un-force it
        // target
        pTexture->mTarget = (flags & CTexture::EFlag::CUBEMAP) ? GL_TEXTURE_CUBE_MAP : (flags & CTexture::EFlag::VOLUME) ? GL_TEXTURE_3D : GL_TEXTURE_2D;
        // internal format
        pTexture->mInternal = flags & CTexture::EFlag::RGBA_S3TC_DXT1 ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : 
                              flags & CTexture::EFlag::RGBA_S3TC_DXT3 ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT : 
                              flags & CTexture::EFlag::RGBA_S3TC_DXT5 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : 
                              flags & CTexture::EFlag::RGBA           ? GL_RGBA : 
                              flags & CTexture::EFlag::RGB            ? GL_RGB : GL_LUMINANCE;
        // format
        pTexture->mFormat  = flags & CTexture::EFlag::BGRA ? GL_BGRA :
                             flags & CTexture::EFlag::BGR  ? GL_BGR  : 
                             flags & CTexture::EFlag::RGBA ? GL_RGBA :
                             flags & CTexture::EFlag::RGB  ? GL_RGB  : GL_RED; // GL_RED, GL_RG, GL_RGB,...
        // set state
        pTexture->mState = CResource::EState::LOADED;
        // done loading
      }, [pTexture, pLoader]() mutable {
        SYS_LOG_NFO("cym::CTextureManager::load(PTextureLoader)::done");
        
// @TODO load tex ASAP using lowes rez/mip, ASYNC the rest of the mips/high-rez, 
//       split opengl part into 2 task, one low-rez one full-rez
  
        uint    faces    = pLoader->flags & CTexture::EFlag::CUBEMAP ? 6 : 1;
        uint    channels = pLoader->bpp == 24 ? 3 : 4;
        uint    width    = 0;
        uint    height   = 0;
        uint    depth    = 0;
        uint    size     = 0;
        uint&   mipmaps  = pLoader->mipmaps;
        uint    flags    = pLoader->flags | CTexture::EFlag::MIPMAPED;
        byte*   stream   = pLoader->mStream->ptr();
        GLenum& target   = pTexture->mTarget; 
        
        GLenum type = GL_UNSIGNED_BYTE;
        
        GLCALL(::glGenTextures(1, &(pTexture->mID)));
        GLCALL(::glBindTexture(target, pTexture->mID));
        
// @TODO is research if 1 is the right value      
        GLCALL(::glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
            
// @TODO replace glTexParameteri w/ glTextureParameteri for ogl >= 4.5 // use CRenderSystem for this
  
        GLCALL(::glTexParameteri(target, GL_TEXTURE_BASE_LEVEL, 0));
        GLCALL(::glTexParameteri(target, GL_TEXTURE_MAX_LEVEL, mipmaps));
        GLCALL(::glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
        GLCALL(::glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
        GLCALL(::glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCALL(::glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        GLCALL(::glTexParameteri(target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
        
// @TODO this might not be good for all formats
        for (uint i = 0; i < faces; i++) {
          target = (faces > 1) ? CTexture::sCubeMapTargets[i] : target;
          width  = pLoader->width;
          height = pLoader->height;
          depth  = pLoader->depth;
          for (ushort j = 0; j < mipmaps && (width || height); j++) {
            size  = cym::mapsize(width, height, depth, channels, flags);
            if (flags & CTexture::EFlag::COMPRESSED) {
              if (flags & CTexture::EFlag::VOLUME) {
                GLCALL(::glCompressedTexImage3D(target, j, pTexture->mInternal, width, height, depth, 0, size, stream));
              } else {
                GLCALL(::glCompressedTexImage2D(target, j, pTexture->mInternal, width, height, 0, size, stream));
              }
            } else {
              if (flags & CTexture::EFlag::VOLUME) {
                GLCALL(::glTexImage3D(target, j, pTexture->mInternal, width, height, depth, 0, pTexture->mFormat, type, stream));
              } else {
                GLCALL(::glTexImage2D(target, j, pTexture->mInternal, width, height, 0, pTexture->mFormat, type, stream));
              }
            }
            stream += size;
          }
        }
        // gen mipmaps
        if (mipmaps <= 1 && flags & CTexture::EFlag::MIPMAPED) {
          GLCALL(::glGenerateMipmap(target));
        }
        // set state
        pTexture->mState = CResource::EState::READY;
        // done w/ opengl
      }, sys::ETask::ASYNC);
      // return texture
      return pTexture;
    } else {
// @TODO return null texture
//       init null texture on CTextureManager::boot() on new CTexture its mId = id of the null texture, until replaced by glGenTextures
      return nullptr;
    }
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TTextureLoader<sys::file>::load(PTexture pTexture) {
    SYS_LOG_NFO("cym::TTextureLoader<sys::file>::load(PTexture)::" << this);
    
    auto pCodec {cym::CCodecManager::getCodec(mFile.ext())};
    
    pCodec->decode(this);
  }
  
  void TTextureLoader<cym::null>::load(PTexture pTexture) {
    SYS_LOG_NFO("cym::TTextureLoader<cym::null>::load(PTexture)::" << this);
    
    auto  pTextureLoader = this; // sys::static_pointer_cast<TTextureLoader<cym::null>>(pResourceLoader);
    auto& tStream        = pTextureLoader->getStream();
    
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
