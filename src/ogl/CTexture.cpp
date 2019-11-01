#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"
#include "ogl/CException.hpp"
#include "gll/gll.hpp"
#include "sys/CFile.hpp"

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
  
  GLvoid CTexture::sampler(ogl::CShader* pShader) {
    throw CException("NOT IMPLEMENTED");
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTexture::CLoader::CLoader(uint nPriority) : CResource::CLoader(nPriority) {
    // nothing
  }
  
  bool CTexture::CLoader::able(const sys::CString& name) {
    static const char* exts[2] = {"dds","tga"};
    return std::end(exts) != std::find(std::begin(exts), std::end(exts), name.substr(name.find_last_of('.')+1).c_str());
  }
  
  CTexture* CTexture::CLoader::load(const sys::CString& name) {
    // @todo: get data using gll::load()
    
    gll::texture oTexture;
    gll::load(oTexture, name);
    
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
    
    
    // @todo: return CTexture*
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CTexture::CManager::CManager() {
    throw CException("NOT IMPLEMENTED");
    // @todo: add default CLoader mLoader; \w lowest priority
  }
  
  CTexture::CManager::~CManager() {
    throw CException("NOT IMPLEMENTED");
  }
  
  CTexture* CTexture::CManager::load(const sys::CString& name) {
    
    // @todo: search for texture in cache
  
    CTexture::CLoader* pUsing    {nullptr};
    uint               nPriority {uint(-1)};
    for (auto& pLoader : mLoaders) {
      if (pLoader->able(name) && pLoader->priority() >= nPriority) {
        pUsing = static_cast<CTexture::CLoader*>(pLoader);
      }
    }
    
    if (pUsing) {
      return pUsing->load(name);
    }
    
    throw CException("Missing CTexture::CLoader!");
  }
}
