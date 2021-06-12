#include "cym/CMaterial.hpp"

namespace cym {
  CChannel::~CChannel() {
    CYM_LOG_NFO("cym::CChannel::~CChannel()::" << this);
  }
  
  CMaterial::~CMaterial() {
    CYM_LOG_NFO("cym::CMaterial::~CMaterial()::" << this);
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CMaterialManager::CMaterialManager() { 
    CYM_LOG_NFO("cym::CTextureManager::CTextureManager()::" << this); 
  }
  
  CMaterialManager::~CMaterialManager() { 
    CYM_LOG_NFO("cym::CMaterialManager::~CMaterialManager()::" << this); 
    mMaterials.clear(); 
  }
}
