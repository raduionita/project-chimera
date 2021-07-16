#ifndef __cym_ccore_hpp__
#define __cym_ccore_hpp__

#include "cym/cym.hpp"
#include "cym/CRenderSystem.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CTexture.hpp"
#include "cym/CModel.hpp"
#include "cym/CShader.hpp"
#include "cym/CCodec.hpp"
#include "cym/CScene.hpp"
#include "cym/CFont.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace cym {
  class CCore : public sys::TSingleton<CCore> {
    protected:
      sys::sptr<CRenderSystem> mRenderSystem;
      
      // CAudioSystem*
      // COverlaySystem*
      // CInputSystem*
      // CPhysicsSystem*
      
      // CTaskManager*
      
      // CSceneManager*
      // CMaterialManager*
      // CBufferManager* ? vbo/ibo
      
      sys::sptr<CShaderManager>   mShaderManager;
      sys::sptr<CMaterialManager> mMaterialManager;
      sys::sptr<CTextureManager>  mTextureManager;
      sys::sptr<CModelManager>    mModelManager;
      sys::sptr<CSceneManager>    mSceneManager;
      
      sys::sptr<CCodecManager>    mCodecManager;
      
      bool mInited {false};
    public:
      CCore();
      ~CCore();
    protected:
      bool init();
      void free();
    public:
      static sys::wptr<CCore> load() { return CCore::getSingleton(); }
    public:
      static sys::sptr<CCodecManager>&         getCodecManager() { return getSingleton()->mCodecManager; }
      virtual inline sys::sptr<CCodecManager>& setCodecManager(sys::sptr<CCodecManager> pManager) { return mCodecManager = pManager; }
      
      static sys::sptr<CShaderManager>& getShaderManager() { return getSingleton()->mShaderManager; }
      virtual inline void               setShaderManager(sys::sptr<CShaderManager> pManager) { mShaderManager = pManager; }
      
      static sys::sptr<CMaterialManager>& getMaterialManager() { return getSingleton()->mMaterialManager; }
      virtual inline void                 setMaterialManager(sys::sptr<CMaterialManager> pManager) { mMaterialManager = pManager; }
      
      static sys::sptr<CTextureManager>& getTextureManager() { return getSingleton()->mTextureManager; }
      virtual inline void                setTextureManager(sys::sptr<CTextureManager> pManager) { mTextureManager = pManager; }
      
      static sys::sptr<CModelManager>& getGeometryManager() { return getSingleton()->mModelManager; }
      virtual inline void              setModelManager(sys::sptr<CModelManager> pManager) { mModelManager = pManager; }
      
      static sys::sptr<CSceneManager>& getSceneManager() { return getSingleton()->mSceneManager; }
      virtual inline void              setSceneManager(sys::sptr<CSceneManager> pManager) { mSceneManager = pManager; }
      
      static sys::sptr<CRenderSystem> setRenderSystem(sys::sptr<CRenderSystem> pSystem) { return getSingleton()->mRenderSystem = pSystem; }
      
// @todo: connects(and befriends) all *System(s)
  };
}

#endif //__cym_ccore_hpp__
