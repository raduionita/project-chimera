#ifndef __ogl_cengine_hpp__
#define __ogl_cengine_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CTexture.hpp"

#include "sys/CSingleton.hpp"

namespace ogl {
  class CEngine : public sys::CSingleton<CEngine> {
    protected:
      // CRenderSystem*
      // CAudioSystem*
      // CInputSystem*
      
      CTexture::CManager* mTextureManager {nullptr};
      
      
    public:
      CEngine();
      ~CEngine();
    public:
      virtual void init();
      virtual void free();
    public:
      inline CTexture::CManager* textureManager() { return mTextureManager; }
      // @todo: connects(and befriends) all *System(s)
  };
}

#endif //__ogl_cengine_hpp__
