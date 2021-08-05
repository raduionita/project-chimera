#include "cym/TInstance.hpp"

namespace cym {
  CInstance::CInstance() {
    // CInstanceRegistry::getSingleton()->mInstances.insert(std::pair<CInstance*,bool&>(this,mLoaded)); 
  }
  
  CInstance::~CInstance() {
    // CInstanceRegistry::getSingleton()->mInstances.erase(this);
  }
  
  CInstanceRegistry::~CInstanceRegistry() {
    for(auto&& [pInstance, tLoaded] : mInstances)
      delete pInstance;
  }
}
