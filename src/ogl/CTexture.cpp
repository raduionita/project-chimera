#include <type_traits>
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
  
  CTextureManager::CTextureManager() { 
    reader(new CDdsTextureReader);
  }
  
  CTextureManager::~CTextureManager() { }
  
  PTexture CTextureManager::load(const sys::CFile& file, const sys::CString& name/*=""*/) {
    log::nfo << "ogl::CTextureManager::load(CFile&,CString&)::" << this << " FILE:" << file << " NAME:" << name << log::end;
    PTexture pTexture;
// @todo: if name is empty then name = filename.ext
// @todo: search cache

    PTextureReader pReader = sys::static_pointer_cast<PTextureReader::type>(reader(file.ext()));
    if (pReader) {
      pTexture = CTexture::from(pReader->read(file));
      
      
      
    } else {
// @todo: pTexture = NULL Texture
// @todo: cache null texture
    }
    



    // use file loader


// @todo: update cache
    return pTexture;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  PTextureStream CDdsTextureReader::read(const sys::CFile& file) {
    log::nfo << "ogl::CDdsTextureReader::read(CFile&)::" << this << " FILE:" << file << log::end;
    PTextureStream pStream {new CTextureStream};
    
    
    
    return pStream;
  }
}
