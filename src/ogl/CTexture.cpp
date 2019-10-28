#include "ogl/CTexture.hpp"
#include "ogl/CShader.hpp"

namespace ogl {
  GLuint CTexture::activate(GLuint slot/*=GL_NOT_FOUND*/) {
    GLCALL(::glActiveTexture(GL_TEXTURE0 + ((slot == GL_NOT_FOUND) ? (mSlot) : (mSlot = slot))));
    GLCALL(::glBindTexture(mTarget, mID));
    return mSlot;
  }
  
  void CTexture::sampler(CShader* pShader) {
    //pShader->sampler(this);
    
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
