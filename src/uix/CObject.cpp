#include "uix/CObject.hpp"

namespace uix {
  std::atomic<INT>   CObject::sId{0};
  CObject::CRegistry CObject::sRegistry;
  
  CObject::CObject() : mId{++sId} {
    CYM_LOG_NFO("uix::CObject::CObject()::" << this << " ID:" << mId);
  }
  
  CObject::~CObject() {
    CYM_LOG_NFO("uix::CObject::~CObject()::" << this << " ID:" << mId);
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::operator const INT() const {
    return mId;
  }
  
  void* CObject::operator new(std::size_t sz) {
    void* ptr = ::operator new(sz);
    CYM_LOG_NFO("uix::CObject::operator new("<< sys::to_hex(reinterpret_cast<std::uintptr_t>(ptr)) <<")");
    sRegistry.insert(static_cast<CObject*>(ptr));
    return ptr;
  }
  
  void CObject::operator delete(void* ptr) {
    // this won't trigger unless the CObject is created w/ new
    if (sRegistry.remove(static_cast<CObject*>(ptr))) {
      ::operator delete(ptr);
      CYM_LOG_NFO("uix::CObject::operator delete("<< sys::to_hex(reinterpret_cast<std::uintptr_t>(ptr)) <<")");
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::CRegistry::CRegistry() {
    CYM_LOG_NFO("uix::CObject::CRegistry::CRegistry()::" << this);
  }
  
  // only on delete CRegistry // when app terminates
  CObject::CRegistry::~CRegistry() {
    CYM_LOG_NFO("uix::CObject::CRegistry::~CRegistry()::" << this);
    while (!mObjects.empty()) {
      CObject* pObject = mObjects.front();
      delete pObject;
    }
  }
  
  bool CObject::CRegistry::insert(CObject* pObject) {
    CYM_LOG_NFO("uix::CObject::CRegistry::insert("<< reinterpret_cast<std::uintptr_t>(pObject) <<") ");
    mObjects.push_back(pObject);
    return mObjects.back() == pObject;
  }
  
  // only on delete CObject
  bool CObject::CRegistry::remove(CObject* pObject) {
    CYM_LOG_NFO("uix::CObject::CRegistry::remove("<< sys::to_hex(reinterpret_cast<std::uintptr_t>(pObject)) <<") ");
    auto size = mObjects.size();
    mObjects.remove(pObject);
    return mObjects.size() < size;
  }
  
  // public //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const int CObject::id() const { return mId; }
}
