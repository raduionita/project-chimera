#ifndef __cym_ccore_hpp__
#define __cym_ccore_hpp__

#include "cym/cym.hpp"
#include "cym/CRenderSystem.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CTexture.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CShader.hpp"
#include "cym/CCodec.hpp"
#include "cym/CScene.hpp"
#include "cym/CFont.hpp"

#include "sys/CSingleton.hpp"
#include "sys/CException.hpp"

namespace cym {
  class CCore : public sys::TSingleton<CCore> {
    protected:
      sys::spo<CRenderSystem> mRenderSystem;
      
      // CAudioSystem*
      // COverlaySystem*
      // CInputSystem*
      // CPhysicsSystem*
      
      // CTaskManager*
      
      // CSceneManager*
      // CMaterialManager*
      // CBufferManager* ? vbo/ibo
      
      sys::spo<CShaderManager>   mShaderManager;
      sys::spo<CMaterialManager> mMaterialManager;
      sys::spo<CTextureManager>  mTextureManager;
      sys::spo<CGeometryManager> mGeometryManager;
      sys::spo<CSceneManager>    mSceneManager;
      
      sys::spo<CCodecManager>    mCodecManager;
      
      bool mInited {false};
    public:
      CCore();
      ~CCore();
    protected:
      bool init();
      void free();
    public:
      static sys::wpo<CCore> load() { return CCore::getSingleton(); }
    public:
      static sys::spo<CCodecManager>&         getCodecManager() { return getSingleton()->mCodecManager; }
      virtual inline sys::spo<CCodecManager>& setCodecManager(sys::spo<CCodecManager> pManager) { return mCodecManager = pManager; }
      
      static sys::spo<CShaderManager>& getShaderManager() { return getSingleton()->mShaderManager; }
      virtual inline void               setShaderManager(sys::spo<CShaderManager> pManager) { mShaderManager = pManager; }
      
      static sys::spo<CMaterialManager>& getMaterialManager() { return getSingleton()->mMaterialManager; }
      virtual inline void                 setMaterialManager(sys::spo<CMaterialManager> pManager) { mMaterialManager = pManager; }
      
      static sys::spo<CTextureManager>& getTextureManager() { return getSingleton()->mTextureManager; }
      virtual inline void                setTextureManager(sys::spo<CTextureManager> pManager) { mTextureManager = pManager; }
      
      static sys::spo<CGeometryManager>& getGeometryManager() { return getSingleton()->mGeometryManager; }
      virtual inline void              setGeometryManager(sys::spo<CGeometryManager> pManager) { mGeometryManager = pManager; }
      
      static sys::spo<CSceneManager>& getSceneManager() { return getSingleton()->mSceneManager; }
      virtual inline void              setSceneManager(sys::spo<CSceneManager> pManager) { mSceneManager = pManager; }
      
      static sys::spo<CRenderSystem> setRenderSystem(sys::spo<CRenderSystem> pSystem) { return getSingleton()->mRenderSystem = pSystem; }
      
// @todo: connects(and befriends) all *System(s)
  };
}

#endif //__cym_ccore_hpp__
