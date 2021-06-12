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
    setModelManager(new cym::CModelManager);
    setShaderManager(new cym::CShaderManager);
    
    setCodecManager(new cym::CCodecManager);
      getCodecManager()->addCodec(new TCodec<CTexture,ECodec::DDS>);
      getCodecManager()->addCodec(new TCodec<CTexture,ECodec::TGA>);
      getCodecManager()->addCodec(new TCodec<CTexture,ECodec::BMP>);
      getCodecManager()->addCodec(new TCodec<CModel,ECodec::DAE>);
      getCodecManager()->addCodec(new TCodec<CModel,ECodec::OBJ>);
    
    
    return mInited = true;
  }
  
  void CCore::free() {
    CYM_LOG_NFO("cym::CCore::free()::" << this);
  }
}
