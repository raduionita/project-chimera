#ifndef __ogl_cengine_hpp__
#define __ogl_cengine_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CTexture.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace ogl {
  class CEngine : public sys::CSingleton<CEngine> {
    protected:
      // CRenderSystem*
      // CAudioSystem*
      // CInputSystem*
      
      ogl::PTextureManager mTextureManager;
    public:
      CEngine();
      ~CEngine();
    protected:
      virtual void init();
      virtual void free();
    public:
      virtual inline ogl::PTextureManager load(ogl::PTextureManager pManager) { mTextureManager = pManager; return mTextureManager; }
// @todo: connects(and befriends) all *System(s)
  };
}

#endif //__ogl_cengine_hpp__
