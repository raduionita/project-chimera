#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CException.hpp"
#include "gll/gll.hpp"
#include "sys/CFile.hpp"

namespace ogl {
  CTexture::CTexture() /*default*/ {
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
    GLCALL(::glGenTextures(1, &mID));
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
  
  CTextureLoader::CTextureLoader(uint nPriority) : ogl::CResourceLoader(nPriority) {
    // nothing
  }
  
  bool CTextureLoader::able(const sys::CString& name) {
    static const char* exts[2] = {"dds","tga"};
    return std::end(exts) != std::find(std::begin(exts), std::end(exts), name.substr(name.find_last_of('.')+1).c_str());
  }
  
  CTexture CTextureLoader::load(const sys::CString& name) {
    log::nfo << "ogl::CTextureLoader::load(std::string&)::" << this << " FILE:" << name << log::end;
    
    gll::texture sTexture;
    if (!gll::texture::load(&sTexture, name)) {
      throw CException("Error loading "+ name, __FILE__, __LINE__);
    }
    
    CTexture oTexture {sTexture.type == gll::CUBEMAP ? CTexture::EType::CUBEMAP : (sTexture.type == gll::VOLUME ? CTexture::EType::VOLUME : CTexture::EType::FLATMAP)};
    
    switch (sTexture.format) {
      case gll::RGBA_S3TC_DXT1: oTexture.format(GL_COMPRESSED_RGBA_S3TC_DXT1_EXT);
      case gll::RGBA_S3TC_DXT3: oTexture.format(GL_COMPRESSED_RGBA_S3TC_DXT3_EXT);
      case gll::RGBA_S3TC_DXT5: oTexture.format(GL_COMPRESSED_RGBA_S3TC_DXT5_EXT);
      case gll::RGBA          : oTexture.format(GL_RGBA); 
      case gll::RGB           : oTexture.format(GL_RGB); 
    }
    
    GLenum target = oTexture.target();
    static GLenum targets[6] = {
      GL_TEXTURE_CUBE_MAP_POSITIVE_X,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
      GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
      GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    
    GLCALL(::glPixelStorei(GL_UNPACK_ALIGNMENT, sTexture.alinment));  // pixel storage mode (1 = byte aligned)
    
    uint iLayer   {0};
    uint nLayers  {uint(sTexture.layers.size())};
    GLenum format {oTexture.format()};
    
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
    
    
    return oTexture;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { }
  
  CTextureManager::~CTextureManager() { }
  
  CTexture CTextureManager::load(const sys::CString& name) {
    
    // @todo: search for texture in cache
  
    CTextureLoader* pUsing    {nullptr};
    uint            nPriority {uint(-1)};
    for (auto& pLoader : mLoaders) {
      if (pLoader->able(name) && pLoader->priority() >= nPriority) {
        pUsing = static_cast<CTextureLoader*>(pLoader);
      }
    }
    
    if (pUsing) {
      return pUsing->load(name);
    }
    
    throw CException("Missing CTexture::CLoader!");
  }
}
