#ifndef __cym_ccore_hpp__
#define __cym_ccore_hpp__

#include "cym/cym.hpp"
#include "cym/CRenderSystem.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CTexture.hpp"
#include "cym/CModel.hpp"
#include "cym/CShader.hpp"
#include "cym/CNode.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace cym {
  class CCore : public sys::TSingleton<CCore> {
    protected:
      cym::PRenderSystem mRenderSystem;
      
      // CAudioSystem*
      // COverlaySystem*
      // CInputSystem*
      // CPhysicsSystem*
      
      // CSceneManager*
      // CMaterialManager*
      // CBufferManager* ? vbo/ibo
      
      cym::PShaderManager  mShaderManager;
      cym::PTextureManager mTextureManager;
      cym::PModelManager   mModelManager;
    public:
      CCore();
      ~CCore();
    protected:
      void init();
      void free();
    public:
      virtual inline void    setShaderManager(cym::PShaderManager pManager) { mShaderManager = pManager; }
      
      virtual inline void    setTextureManager(cym::PTextureManager pManager) { mTextureManager = pManager; }
      static PTextureManager getTextureManager() { return instance()->mTextureManager; }
      //static inline PTexture loadTexture(const sys::CString& name, const sys::CFile& file) { return instance()->mTextureManager->load(name,file); }
      
      virtual inline void  setModelManager(cym::PModelManager   pManager) { mModelManager = pManager; }
      static PModelManager getModelManager() { return instance()->mModelManager; }
      //static inline PModel loadModel(const sys::CString& name, const sys::CFile& file) { return instance()->mModelManager->load(name,file); }
      
      static PRenderSystem setRenderSystem(PRenderSystem system) { return instance()->mRenderSystem = system; }
      
      // @todo: connects(and befriends) all *System(s)
  };
}

#endif //__cym_ccore_hpp__
