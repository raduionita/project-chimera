#include "cym/uix/CObject.hpp"

namespace cym::uix {
  std::atomic<INT>   CObject::sId{0};
  CObject::CRegistry CObject::sRegistry;
  
  CObject::CObject() : mId{++sId} {
    log::nfo << "uix::CObject::CObject()::" << this << " ID:" << mId << log::end;
  }
  
  CObject::~CObject() {
    log::nfo << "uix::CObject::~CObject()::" << this << " ID:" << mId << log::end;
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::operator const INT() const {
    return mId;
  }
  
  void* CObject::operator new(std::size_t sz) {
    void* ptr = ::operator new(sz);
    log::nfo << "uix::CObject::operator new("<< reinterpret_cast<std::uintptr_t>(ptr) <<")" << log::end;
    sRegistry.insert(static_cast<CObject*>(ptr));
    return ptr;
  }
  
  void CObject::operator delete(void* ptr) {
    // this won't trigger unless the CObject is created w/ new
    log::nfo << "uix::CObject::operator delete("<< reinterpret_cast<std::uintptr_t>(ptr) <<")" << log::end;
    if (sRegistry.remove(static_cast<CObject*>(ptr))) {
      ::operator delete(ptr);
    }
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::CRegistry::CRegistry() {
    log::nfo << "uix::CObject::CRegistry::CRegistry()::" << this << log::end;
  }
  
  // only on delete CRegistry // when app terminates
  CObject::CRegistry::~CRegistry() {
    log::nfo << "uix::CObject::CRegistry::~CRegistry()::" << this << log::end;
    while (!mObjects.empty()) {
      CObject* pObject = mObjects.front();
      delete pObject;
    }
  }
  
  bool CObject::CRegistry::insert(CObject* pObject) {
    log::nfo << "uix::CObject::CRegistry::insert("<< reinterpret_cast<std::uintptr_t>(pObject) <<") " << log::end;
    mObjects.push_back(pObject);
    return mObjects.back() == pObject;
  }
  
  // only on delete CObject
  bool CObject::CRegistry::remove(CObject* pObject) {
    log::nfo << "uix::CObject::CRegistry::remove("<< reinterpret_cast<std::uintptr_t>(pObject) <<") " << log::end;
    auto size = mObjects.size();
    mObjects.remove(pObject);
    return mObjects.size() < size;
  }
  
  // public //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const int CObject::id() const { return mId; }
}
