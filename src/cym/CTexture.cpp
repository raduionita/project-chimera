#include "cym/CTexture.hpp"
#include "cym/CShader.hpp"
#include "cym/CException.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  CTexture::CTexture(const std::string& tName) : cym::CResource(tName) {
    CYM_LOG_NFO("cym::CTexture::CTexture()::" << this);
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::CTexture(sys::sptr<CTextureLoader> rLoader) {
    CYM_LOG_NFO("cym::CTexture::CTexture(sys::sptr<CTextureLoader>)::" << this);
    load(rLoader);
  }
  
  CTexture::~CTexture() {
    CYM_LOG_NFO("cym::CTexture::~CTexture()::" << this << " NAME:" << mName);
    GLCALL(::glDeleteTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, 0));
  }
  
  void CTexture::load(sys::sptr<CTextureLoader> rLoader) {
    CYM_LOG_NFO("cym::CTexture::load(sys::sptr<CTextureLoader>)::" << this);
    
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
  
  void CTexture::filtering(enum cym::CTexture::EFiltering eFiltering) {
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
  
  void CTexture::wrapping(enum cym::CTexture::EWrapping eWrapping) {
    GLCALL(::glBindTexture(mTarget, mID));
      
    GLenum wrapping = GL_NONE;
    if(eWrapping | EWrapping::CLAMP_TO_EDGE)
      wrapping = GL_CLAMP_TO_EDGE;
    else if(eWrapping | EWrapping::CLAMP_TO_BORDER)
      wrapping = GL_CLAMP_TO_BORDER;
    else if(eWrapping | EWrapping::REPEAT)
      wrapping = GL_REPEAT;
      
    GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, wrapping));
    if(mHeight > 1 || mTarget == GL_TEXTURE_2D || mTarget == GL_TEXTURE_1D_ARRAY)
      GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, wrapping));
    if(mDepth > 1 || mTarget == GL_TEXTURE_3D || mTarget == GL_TEXTURE_CUBE_MAP || mTarget == GL_TEXTURE_2D_ARRAY)
      GLCALL(::glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, wrapping));
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { 
    CYM_LOG_NFO("cym::CTextureManager::CTextureManager()::" << this); 
  }
  
  CTextureManager::~CTextureManager() { 
    CYM_LOG_NFO("cym::CTextureManager::~CTextureManager()::" << this); 
    //mTextures.clear(); 
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void TTextureLoader<sys::CFile>::load(sys::sptr<CResourceLoader> pResourceLoader) {
    CYM_LOG_NFO("cym::TTextureLoader<sys::CFile>::load(sys::sptr<CResourceLoader>)::" << this);
    
    auto pCodec = cym::CCodecManager::getCodec(mFile.ext());
    
    pCodec->decode(pResourceLoader);
  }
}
