#include "cym/CCore.hpp"

namespace cym {
  CCore::CCore() {
    SYS_LOG_NFO("cym::CCore::CCore()::" << this);
    (!mInited) && init();
  }
  
  CCore::~CCore() {
    SYS_LOG_NFO("cym::CCore::~CCore::" << this);
    free();
  }
  
  bool CCore::init() {
    SYS_LOG_NFO("cym::CCore::init()::" << this);
  
    cym::CMaterialManager::boot();
    cym::CTextureManager::boot();
    cym::CGeometryManager::boot();
    cym::CShaderManager::boot();
    cym::CSceneManager::boot();
  
    cym::CCodecManager::boot();
      cym::CCodecManager::addCodec(new TCodec<CTexture,ECodec::DDS>);
      cym::CCodecManager::addCodec(new TCodec<CTexture,ECodec::TGA>);
      cym::CCodecManager::addCodec(new TCodec<CTexture,ECodec::BMP>);
      cym::CCodecManager::addCodec(new TCodec<CGeometry,ECodec::DAE>);
      cym::CCodecManager::addCodec(new TCodec<CGeometry,ECodec::OBJ>);
      cym::CCodecManager::addCodec(new TCodec<CScene,ECodec::SCENE>);
  
    cym::CRenderSystem::boot();
    
    return mInited = true;
  }
  
  void CCore::free() {
    SYS_LOG_NFO("cym::CCore::free()::" << this);
  }
}
