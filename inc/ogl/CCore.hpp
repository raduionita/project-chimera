#ifndef __ogl_ccore_hpp__
#define __ogl_ccore_hpp__

#include "ogl/ogl.hpp"
#include "ogl/CRenderSystem.hpp"
#include "ogl/CTexture.hpp"
#include "ogl/CModel.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace ogl {
  class CCore : public sys::CSingleton<CCore> {
    protected:
      PRenderSystem mRenderSystem;
      // CAudioSystem*
      // COverlaySystem*
      // CInputSystem*
      // CPhysicsSystem*
      
      // CSceneManager*
      // CModelManager*
      // CTextureManager*
      // CMaterialManager*
      // CShaderManager*
      
      ogl::PTextureManager mTextureManager;
      ogl::PModelManager   mModelManager;
    public:
      CCore();
      ~CCore();
    protected:
      void init();
      void free();
    public:
      virtual inline ogl::PTextureManager load(ogl::PTextureManager pManager) { mTextureManager = pManager; return mTextureManager; }
    
      static PTextureManager getTextureManager() { return instance()->mTextureManager; }
      static PModelManager getModelManager() { return instance()->mModelManager; }
      
      static PRenderSystem setRenderSystem(PRenderSystem system) { return instance()->mRenderSystem = system; }
// @todo: connects(and befriends) all *System(s)
  };
}

#endif //__ogl_ccore_hpp__
