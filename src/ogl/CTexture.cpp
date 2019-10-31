#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CException.hpp"
#include "gll/gll.hpp"

namespace ogl {
  CTexture::CTexture() {
    // after creation mMipmaps = request || generated || or 0 of option = no_mipmaps
    mMipmaps = 1 + glm::floor(glm::log2(glm::max(glm::max(mWidth,mHeight),mDepth)));
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
  
  GLvoid CTexture::sampler(CShader* pShader) {
    throw CException("NOT IMPLEMENTED");
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTexture::CLoader::CLoader() {
    
  }
  
  bool CTexture::CLoader::able(const sys::CString& file) {
    sys::CString::size_type pos{file.find_last_of('.')};
    if (pos == sys::CString::npos) {
      
      // @todo: what file extensions does this loader support
      
      return false;
    }
    return false;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTexture::CManager::CManager() {
    throw CException("NOT IMPLEMENTED");
    // @todo: add default CLoader mLoader; \w lowest priority
  }
  
  CTexture::CManager::~CManager() {
    throw CException("NOT IMPLEMENTED");
  }
  
  CTexture* CTexture::CManager::load(const CString& file) {
    // @todo: search for texture in cache
    // for each pLoader in mLoaders 
    throw CException("NOT IMPLEMENTED");
  }
}
