#ifndef __ogl_cengine_hpp__
#define __ogl_cengine_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CTexture.hpp"
#include "ogl/CModel.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace ogl {
  class CCore : public sys::CSingleton<CCore> {
    protected:
      // CRenderSystem*
      // CAudioSystem*
      // COverlaySystem*
      // CInputSystem*
      
      // CSceneManager*
      // CModelManager*
      // CTextureManager*
      // CMaterialManager*
      // CShaderManager*
      
      ogl::PTextureManager mTextureManager;
    public:
      CCore();
      ~CCore();
    protected:
      virtual void init();
      virtual void free();
    public:
      virtual inline ogl::PTextureManager load(ogl::PTextureManager pManager) { mTextureManager = pManager; return mTextureManager; }
// @todo: connects(and befriends) all *System(s)
  };
}

#endif //__ogl_cengine_hpp__
