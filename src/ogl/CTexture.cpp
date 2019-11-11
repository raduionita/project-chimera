#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CException.hpp"
#include "ogl/CCodec.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"

namespace ogl {
  CTexture::CTexture() /*default*/ {
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::CTexture(GLenum target) : mTarget{target} {
    GLCALL(::glGenTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  CTexture::CTexture(EType t) : mType{t} {
    type(mType);
    GLCALL(::glGenTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  CTexture::~CTexture() {
    GLCALL(::glDeleteTextures(1, &mID));
    GLCALL(::glBindTexture(mTarget, 0));
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
  
  GLvoid CTexture::bind(GLuint slot) {
    GLCALL(::glActiveTexture(GL_TEXTURE0 + (mSlot = slot)));
    GLCALL(::glBindTexture(mTarget, mID));
  }
  
  GLvoid CTexture::sampler(ogl::CShader* pShader) {
    throw CException("NOT IMPLEMENTED");
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CTextureLoader::able(const ogl::CString& name) const { 
    return name.find_last_of(".dds") != sys::CString::npos; 
  }
  
  PTexture CTextureLoader::load(const sys::CFile& file) const {
    log::nfo << "ogl::CTextureLoader::load(sys::CFile&)::" << this << " FILE:" << file << log::end;
    
    sys::throw_if(file.empty(), "No file no texture");
    
    
    
    // for each registered codec
    for (auto& [zType, pCodec] : CCodecManager::sCodecs) {
      if (pCodec->able(file)) {
        PResourceData data {pCodec->decode(file)};
        
        return new CTexture {data};
      }
    }
    
    
    
    

  
    uint nComponents = (head.pf.fourcc == EFlag::FOURCC) || (head.pf.bpp == 24) ? 3 : 4;
    bool bCompressed = false;
    uint nLayers     = pTexture->type() == CTexture::EType::CUBEMAP ? 6 : 1;
    
    if (head.pf.flags & EFlag::FOURCC) {
      switch (head.pf.fourcc) {
        case EFlag::FOURCC_DTX1: pTexture->format(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
        case EFlag::FOURCC_DTX3: pTexture->format(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
        case EFlag::FOURCC_DTX5: pTexture->format(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
        default :sys::throw_if(true, "Unknownd .DDS COMPRESSED RGBA format");
      }
      bCompressed = true;
    } else if (head.pf.flags == EFlag::RGBA && head.pf.bpp == 32) {
      pTexture->format(GL_RGBA);
    } else if (head.pf.flags == EFlag::RGB && head.pf.bpp == 32) {
      pTexture->format(GL_RGBA);
    } else if (head.pf.flags == EFlag::RGB && head.pf.bpp == 24) {
      pTexture->format(GL_RGB);
    } else if (head.pf.bpp == 8) {
      // @todo: luminance // otex->components = 1
      sys::throw_if(true, "Unsupported .DDS LUMINANCE format");
    } else {
      sys::throw_if(true, "Unknown .DDS format");
    }
    
    pTexture->width(clamp2one(head.width));
    pTexture->height(clamp2one(head.height));
    pTexture->depth(head.depth);
    pTexture->mipmaps(head.mipmaps == 0 ? 1 : head.mipmaps);
    
    static GLenum targets[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    
    GLCALL(::glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
    
    GLenum target = pTexture->target();
    uint   width  = 0;
    uint   height = 0;
    uint   depth  = 0;
    
    for(ushort i = 0; i < nLayers; i++) {
      if(nLayers > 1)
        target = targets[i];
      // for this layer
      width  = head.width;
      height = head.height;
      depth  = head.depth ? head.depth : 1;
    }
    
    // CTexture pTexture {sTexture.type == gll::CUBEMAP ? CTexture::EType::CUBEMAP : (sTexture.type == gll::VOLUME ? CTexture::EType::VOLUME : CTexture::EType::FLATMAP)};
    
    
    

    
    GLCALL(::glPixelStorei(GL_UNPACK_ALIGNMENT, sTexture.alinment));  // pixel storage mode (1 = byte aligned)
    
    uint iLayer   {0};
    uint nLayers  {uint(sTexture.layers.size())};
    GLenum format {pTexture.format()};
    
    for (auto& pLayer : sTexture.layers) {
      if(sTexture.layers.size() > 1) {
        target = targets[iLayer];
      }
      
      uint iMipmap {0};
      for (auto& pMipmap : pLayer->mipmaps) {
        if (sTexture.compressed) {
          if (sTexture.type == gll::VOLUME) {
            GLCALL(::glCompressedTexImage3D(target, iMipmap, format, pMipmap->width, pMipmap->height, pMipmap->depth, 0, pMipmap->size, pMipmap->data));
          } else {
            GLCALL(::glCompressedTexImage2D(target, iMipmap, format, pMipmap->width, pMipmap->height, 0, pMipmap->size, pMipmap->data));
          }
        } else {
          if (sTexture.type == gll::VOLUME) {
            GLCALL(::glTexImage3D(target, iMipmap, format, pMipmap->width, pMipmap->height, pMipmap->depth, 0, format, GL_UNSIGNED_BYTE, pMipmap->data));
          } else {
            GLCALL(::glTexImage2D(target, iMipmap, format, pMipmap->width, pMipmap->height, 0, format, GL_UNSIGNED_BYTE, pMipmap->data));
          }
        }
        iMipmap++;
      }
      iLayer++;
    }
    
    gll::texture::free(&sTexture);
    
    // @todo: create texture object + call ::glXXX methods
      // use ::glTexStorage2D // allocate
      // +
      // use ::glTexSubImage2D // put
  
      // glBindTexture(GL_TEXTURE_2D, tid);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount-1); // opengl likes array length of mipmaps
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // don't forget to enable mipmaping
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      
      // for (unsigned int i=0; i<mipMapCount; i++) {
        // glCompressedTexImage2D(GL_TEXTURE_2D, i, format, w, h, 0, size, buffer + offset)
      //
      
      // discard old mipmaps
      // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipMapCount-1);
    
      
    // @todo: if options = MIPMAPS && sTexture.mipmaps <= 1
      // @todo: glGenerateMipmap(target);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { 
    loader(new CTextureLoader);
  }
  
  CTextureManager::~CTextureManager() { }
  
  PTexture CTextureManager::load(const sys::CString& name) {
    PTextureManager& self = CTextureManager::instance();
    log::nfo << "ogl::CTextureManager::load(sys::CFile&)::" << self << " FILE:" << name << log::end;
    
    // @todo: search for texture in cache
    // @todo: these loaders MUST be shared pointers
    CTextureLoader* pUsable {nullptr};
    for (auto& pLoader : self->mLoaders) {
      if (pLoader->able(name)) {
        pUsable = static_cast<CTextureLoader*>(pLoader);
      }
    }
    
    if (pUsable) {
      return pUsable->load(name);
    }
    
    throw CException("Missing CTexture::CLoader!");
  }
}
