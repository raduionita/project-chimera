#include "cym/CTexture.hpp"
#include "cym/CShader.hpp"
#include "cym/CException.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"
#include "cym/CCodec.hpp"

namespace cym {
  CTexture::CTexture() /*default*/ {
    log::nfo << "cym::CTexture::CTexture()::" << this << log::end;
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::CTexture(PTextureData pData) {
    log::nfo << "cym::CTexture::CTexture(PTextureData)::" << this << log::end;
    load(pData);
  }
  
  CTexture::~CTexture() {
    log::nfo << "cym::CTexture::~CTexture()::" << this << log::end;
    GLCALL(::glDeleteTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, 0));
  }
  
  void CTexture::load(PTextureData pData) {
    log::nfo << "cym::CTexture::load(PTextureData)::" << this << log::end;
    CTextureData::SInfo& info = pData->mInfo;
    
    static GLenum targets[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    uint   faces    = info.flags & EFlag::CUBEMAP ? 6 : 1;
    uint   channels = info.bpp == 24 ? 3 : 4;
    uint   width    = 0;
    uint   height   = 0;
    uint   depth    = 0;
    uint   size     = 0;
    uint&  mipmaps  = info.mipmaps;
    uint   flags    = info.flags | EFlag::MIPMAPED;
    byte*  data     = pData->mStream->ptr();
    GLenum target   = (flags & EFlag::CUBEMAP) ? GL_TEXTURE_CUBE_MAP : (flags & EFlag::VOLUME) ? GL_TEXTURE_3D : GL_TEXTURE_2D;
    GLenum internal = flags & EFlag::RGBA_S3TC_DXT1 ? GL_COMPRESSED_RGBA_S3TC_DXT1_EXT : flags & EFlag::RGBA_S3TC_DXT3 ? GL_COMPRESSED_RGBA_S3TC_DXT3_EXT : flags & EFlag::RGBA_S3TC_DXT5 ? GL_COMPRESSED_RGBA_S3TC_DXT5_EXT : flags & EFlag::RGBA ? GL_RGBA : flags & EFlag::RGB ? GL_RGB : GL_LUMINANCE;
    GLenum format   = GL_RGBA; // GL_RED, GL_RG, GL_RGB,...
    GLenum type     = GL_UNSIGNED_BYTE;
    
    mTarget = target;
    mFormat = internal;
    
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
      if(faces > 1) target = targets[i];
      width  = info.width;
      height = info.height;
      depth  = info.depth;
      for (ushort j = 0; j < mipmaps && (width || height); j++) {
        size  += CTextureData::size(width, height, depth, channels, flags);
        if (flags & EFlag::COMPRESSED) {
          if (flags & EFlag::VOLUME)
            GLCALL(::glCompressedTexImage3D(target, j, internal, width, height, depth, 0, size, data));
          else
            GLCALL(::glCompressedTexImage2D(target, j, internal, width, height, 0, size, data));
        } else {
          if (flags & EFlag::VOLUME) {
            GLCALL(::glTexImage3D(target, j, internal, width, height, depth, 0, format, type, data));
          }
          else
            GLCALL(::glTexImage2D(target, j, internal, width, height, 0, format, type, data));
        }
        data += size;
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
  
  CTextureManager::CTextureManager() : cym::CResourceManager("texture") {
    log::nfo << "cym::CTextureManager::CTextureManager()::" << this << log::end;
    // @todo: this should be overwriteable...put it in the engine init method
    loader(new CFileTextureLoader);
  }
  
  CTextureManager::~CTextureManager() {
    log::nfo << "cym::CTextureManager::~CTextureManager()::" << this << log::end;
  }
  
  // loaders /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CFileTextureLoader::CFileTextureLoader() : CTextureLoader<sys::CFile>() {
    log::nfo << "cym::CFileTextureLoader::CFileTextureLoader()::" << this << log::end;
    // @todo: move this to engine/code init 
    codec(new CDDSCodec);
  }
  
  CFileTextureLoader::~CFileTextureLoader() {
    log::nfo << "cym::CFileTextureLoader::~CFileTextureLoader()::" << this << log::end;
  }
  
  PCodec CFileTextureLoader::codec(const sys::CString& ext) { 
    auto it = mCodecs.find(ext);
    if (it != mCodecs.end()) { return it->second; }
    return nullptr;
  }
  
  PTextureData CFileTextureLoader::load(const sys::CFile& file) {
    log::nfo << "cym::CFileTextureLoader::load(CFile&)::" << this << " FILE:" << file << log::end;  
    // start w/ a stream
    
    PCodec pCodec = codec(file.ext());
    
    return sys::static_pointer_cast<PTextureData::type>(pCodec->decode(file));
  }
}
