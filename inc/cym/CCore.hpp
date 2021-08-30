#ifndef __cym_ccore_hpp__
#define __cym_ccore_hpp__

#include "cym/cym.hpp"
#include "cym/CMaterial.hpp"
#include "cym/CTexture.hpp"
#include "cym/CGeometry.hpp"
#include "cym/CShader.hpp"
#include "cym/CCodec.hpp"
#include "cym/CScene.hpp"
#include "cym/CFont.hpp"

#include "cym/CRenderSystem.hpp"

#include "sys/TSingleton.hpp"
#include "sys/CException.hpp"

namespace cym {
  class CCore : public sys::TSingleton<CCore> {
    protected:
      bool mInited {false};
    public:
      CCore();
      ~CCore();
    protected:
      bool init();
      void free();
    public:
      static void boot() { CCore::getSingleton(); }
    public:
      // CAudioSystem*
      // COverlaySystem*
      // CInputSystem*
      // CPhysicsSystem*
      
      // CTaskManager*
      
      // CBufferManager* ? vbo/ibo
      
      // static cym::CCodecManager&    getCodecManager() { return CCodecManager::getSingleton(); }
      //
      // static cym::CShaderManager&   getShaderManager() { return CShaderManager::getSingleton(); }
      //
      // static cym::CMaterialManager& getMaterialManager() { return CMaterialManager::getSingleton(); }
      //
      // static cym::CTextureManager&  getTextureManager() { return CTextureManager::getSingleton(); }
      //
      // static cym::CGeometryManager& getGeometryManager() { return CGeometryManager::getSingleton(); }
      //
      // static cym::CSceneManager&    getSceneManager() { return CSceneManager::getSingleton(); }
      //
      // static cym::CRenderSystem&    getRenderSystem() { return CRenderSystem::getSingleton(); }
      
// @todo: connects(and befriends) all *System(s)
  };
}

#endif //__cym_ccore_hpp__
