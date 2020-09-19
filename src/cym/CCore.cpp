#include "cym/CCore.hpp"

namespace cym {
  CCore::CCore() {
    log::nfo << "cym::CCore::CCore()::" << this << log::end;
    init();
  }
  
  CCore::~CCore() {
    log::nfo << "cym::CCore::~CCore::" << this << log::end;
    free();
  }
  
  void CCore::init() {
    setTextureManager(new cym::CTextureManager);
    setModelManager(new cym::CModelManager);
    setShaderManager(new cym::CShaderManager);
  }
  
  void CCore::free() {
    
  }
}
