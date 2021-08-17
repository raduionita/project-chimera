#include "cym/CRenderSystem.hpp"

namespace cym {
  CRenderSystem::CRenderSystem() { 
    SYS_LOG_NFO("cym::CRenderSystem::CRenderSystem()::" << this);
    (!mInited) && (init());
  }
  
  CRenderSystem::~CRenderSystem() { 
    SYS_LOG_NFO("cym::CRenderSystem::~CRenderSystem()::" << this);
    free();
  }
  
  bool CRenderSystem::init() {
    SYS_LOG_NFO("cym::CRenderSystem::init()::" << this);
    
    // render system flags/states // set defaults
    
    // blending
    useBlend(true);                                     // GLCALL(::glEnable(GL_BLEND))
    setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // GLCALL(::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    // backface culling
    useCullFace(true);    // GLCALL(::glEnable(GL_CULL_FACE))
    setCullFace(GL_BACK); // GLCALL(::glCullFace(mCullFace))
    // front face vertex order
    setFrontFace(GL_CCW);  // GLCALL(::glFrontFace(mFontFace))
    // depth test
    useDepthTest(true);      // GLCALL(::glEnable(GL_DEPTH_TEST));
    setDepthFunc(GL_LEQUAL); // GLCALL(::glDepthFunc(GL_LEQUAL))
    setDepthMask(GL_TRUE);   // GLCALL(::glDepthMask(GL_TRUE))
    
    // setViewport(x,y,w,h);
    // GLCALL(::glViewport(0,0,tArea.w,tArea.h));
    
    // setPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // GLCALL(::glEnable(GL_POLYGON_OFFSET_LINE));
    // GLCALL(::glPolygonOffset(-1.0f, -1.0f));
    // GLCALL(::glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)); // GL_POINT GL_FILL(default)
    // GLCALL(::glLineWidth(1.0f));
    
    return true;
  }
  
  void CRenderSystem::free() {
    SYS_LOG_NFO("cym::CRenderSystem::free()::" << this);
  }
}
