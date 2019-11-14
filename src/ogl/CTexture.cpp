#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CException.hpp"
#include "sys/CFile.hpp"
#include "sys/CStream.hpp"

namespace ogl {
  CTexture::CTexture() /*default*/ {
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    // mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
  }
  
  CTexture::CTexture(PTextureStream stream) {
    load(stream);
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
  
  void CTexture::load(PTextureStream) {
    log::nfo << "ogl::CTexture::load(PTextureStream)::" << this << log::end;
// @todo: create the texture
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
  
  GLvoid CTexture::sampler(ogl::CShader*) {
    throw CException("NOT IMPLEMENTED");
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CFileTextureBuilder::CFileTextureBuilder() {
    loader(new CTGATextureLoader);
    loader(new CDDSTextureLoader);
  }
  
  PTexture CFileTextureBuilder::from(const sys::CFile& file) {
    log::nfo << "ogl::CFileTextureBuilder::from(sys::CFile&)::" << this << " FILE:" << file.path() << log::end;

    for (auto& pLoader : mLoaders) {
      if (pLoader->type().compare(file.extension()) == 0) {
        return new CTexture {pLoader->from(file)};
      }
    }
    
    throw CException("Missing CTextureLoader!", __FILE__, __LINE__);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { 
    builder(new CDataTextureBuilder);
    builder(new CFileTextureBuilder);
  }
  
  CTextureManager::~CTextureManager() { }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PTextureStream CDDSTextureLoader::from(const sys::CFile& file) {
    log::nfo << "ogl::CDDSTextureLoader::from(sys::CFile&)::" << this << " FILE:" << file << log::end;
    // @todo: open file
    
    CTextureStream* pStream {new CTextureStream};
    
    
    
    
    return pStream;
  }
}
