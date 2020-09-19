#include "cym/CResource.hpp"

namespace cym {
  CResourceLoader::CResourceLoader() {
    log::nfo << "cym::CResourceLoader::CResourceLoader()::" << this << log::end;
  }
  
  CResourceLoader::~CResourceLoader() {
    log::nfo << "cym::CResourceLoader::~CResourceLoader()::" << this << log::end;
  }
  
  CResourceManager::CResourceManager(const sys::CString& scope) : mScope{scope} {
    log::nfo << "cym::CResourceManager::CResourceManager(" << mScope << ")::" << this << log::end;
  }
  
  CResourceManager::~CResourceManager() {
    log::nfo << "cym::CResourceManager::~CResourceManager(" << mScope << ")::" << this << log::end;
  }
}
