#include "cym/CCore.hpp"

namespace cym {
  CCore::CCore() {
    CYM_LOG_NFO("cym::CCore::CCore()::" << this);
    
    (!mInited) && init();
  }
  
  CCore::~CCore() {
    CYM_LOG_NFO("cym::CCore::~CCore::" << this);
    free();
  }
  
  bool CCore::init() {
    CYM_LOG_NFO("cym::CCore::init()::" << this);
    
    setMaterialManager(new cym::CMaterialManager);
    setTextureManager(new cym::CTextureManager);
    setGeometryManager(new cym::CGeometryManager);
    setShaderManager(new cym::CShaderManager);
    setSceneManager(new cym::CSceneManager);
    
    setCodecManager(new cym::CCodecManager);
      getCodecManager()->addCodec(new TCodec<CTexture,ECodec::DDS>);
      getCodecManager()->addCodec(new TCodec<CTexture,ECodec::TGA>);
      getCodecManager()->addCodec(new TCodec<CTexture,ECodec::BMP>);
      getCodecManager()->addCodec(new TCodec<CGeometry,ECodec::DAE>);
      getCodecManager()->addCodec(new TCodec<CGeometry,ECodec::OBJ>);
      getCodecManager()->addCodec(new TCodec<CScene,ECodec::SCENE>);
    
    return mInited = true;
  }
  
  void CCore::free() {
    CYM_LOG_NFO("cym::CCore::free()::" << this);
  }
}
