#include "cym/CMaterial.hpp"

namespace cym {
  CChannel::~CChannel() {
    SYS_LOG_NFO("cym::CChannel::~CChannel()::" << this);
  }
  
  CMaterial::~CMaterial() {
    SYS_LOG_NFO("cym::CMaterial::~CMaterial()::" << this);
  }
  
  // manager /////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CMaterialManager::CMaterialManager() { 
    SYS_LOG_NFO("cym::CTextureManager::CTextureManager()::" << this); 
  }
  
  CMaterialManager::~CMaterialManager() { 
    SYS_LOG_NFO("cym::CMaterialManager::~CMaterialManager()::" << this); 
    mMaterials.clear(); 
  }
}
