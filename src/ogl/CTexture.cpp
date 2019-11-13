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
  
  CFileTextureBuilder::CFileTextureBuilder() {
    loader(new CDDSTextureLoader);
    loader(new CTGATextureLoader);
  }
  
  PTextureStream CFileTextureBuilder::from(const sys::CFile& file) {
    log::nfo << "ogl::CFileTextureBuilder::from(sys::CString&)::" << this << " FILE:" << file << log::end;

    
    
    
    throw CException("Missing CTextureLoader!", __FILE__, __LINE__);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTextureManager::CTextureManager() { 
    builder(new CFileTextureBuilder);
  }
  
  CTextureManager::~CTextureManager() { }
  
  PTexture CTextureManager::load(const sys::CString& name) {
    static PTextureManager& self = CTextureManager::instance();
    log::nfo << "ogl::CTextureManager::load(sys::CString&)::" << self << " NAME:" << name << log::end;
    // don't try to use another builder if the process has already started 
    static auto pBuilder = sys::static_pointer_cast<CFileTextureBuilder>(self->builder("file"));
// @todo: search for texture in cache
    PTextureStream pStream  {pBuilder->from(name)};
// @todo: return null texture (stream) from cache if can't build texture
    PTexture       pTexture {pStream};
// @todo: put texture in cache
    return pTexture;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PTextureStream CTextureLoader::load(const sys::CString& file) {
    static PTextureManager& mang = CTextureManager::instance();
    log::nfo << "ogl::CTextureLoader::load(sys::CString&)::" << " FILE:" << file << log::end;
    CTextureLoader* pUsable {nullptr};
// @todo: these loaders SHOULD be shared pointers
    for (auto& pLoader : mang->loaders()) {
      if (pLoader->able(file)) {
        pUsable = static_cast<CTextureLoader*>(pLoader);
        return pUsable->from(file);
      }
    }
// @todo: return null texture from cache
    throw sys::CException("Missing CTexture::CLoader!", __FILE__, __LINE__);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PTextureStream CDDSTextureLoader::from(const sys::CString& file) {
    log::nfo << "ogl::CDDSTextureLoader::from(sys::CString&)::" << this << " FILE:" << file << log::end;
    // @todo: open file
    
    CTextureStream* pStream {new CTextureStream};
    
    
    return pStream;
  }
}
