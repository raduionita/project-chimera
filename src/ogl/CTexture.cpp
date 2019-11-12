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
  
  CTextureManager::CTextureManager() { 
    loader(new CDDSTextureLoader);
    loader(new CTGATextureLoader);
  }
  
  CTextureManager::~CTextureManager() { }
  
  PTexture CTextureManager::load(const sys::CString& name) {
    static PTextureManager& self = CTextureManager::instance();
    log::nfo << "ogl::CTextureManager::load(sys::CString&)::" << self << " NAME:" << name << log::end;
// @todo: search for texture in cache
    CTextureLoader* pUsable {nullptr};
// @todo: these loaders SHOULD be shared pointers
    for (auto& pLoader : self->mLoaders) {
      if (pLoader->able(name)) {
        pUsable = static_cast<CTextureLoader*>(pLoader);
        auto pStream  = pUsable->load(name);
        auto pTexture = new CTexture(pStream);
// @todo: put texture in cache
        return pTexture;
      }
    }
// @todo: return null texture from cache
    throw CException("Missing CTexture::CLoader!");
  }
  
  PTexture CTextureManager::load(PTextureStream stream, const CString& name) {
    return ogl::PTexture();
  }
}
