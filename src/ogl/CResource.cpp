#include "ogl/CResource.hpp"

namespace ogl {
  CResourceManager::CResourceManager() {
    
  }
  
  CResourceManager::~CResourceManager() {
    for (auto& pLoader : mLoaders) {
      delete pLoader;
      pLoader = nullptr;
    }
  }
}
