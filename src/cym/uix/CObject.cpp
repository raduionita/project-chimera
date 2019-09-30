#include "cym/uix/CObject.hpp"

namespace cym { namespace uix {
  std::atomic<INT>   CObject::sId{0};
  CObject::CRegistry CObject::sRegistry;
  
  CObject::CObject() : mId{++sId} {
    log::nfo << "uix::CObject::CObject()::" << this << " ID:" << mId << log::end;
    mId && sRegistry.insert(this); // only if it has a valid mId
  }
  
  CObject::~CObject() {
    log::nfo << "uix::CObject::~CObject()::" << this << " ID:" << mId << log::end;
    mId && sRegistry.remove(this); // only if it has a valid mId
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::operator const INT() const {
    return mId;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::CRegistry::CRegistry() {
    log::nfo << "uix::CObject::CRegistry::CRegistry()::" << this << log::end;
  }
  
  CObject::CRegistry::~CRegistry() {
    log::nfo << "uix::CObject::CRegistry::~CRegistry()::" << this << log::end;
    for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
      if (*it) {
        delete (*it);
      }
    }
  }
  
  bool CObject::CRegistry::insert(CObject* pObject) {
    log::nfo << "uix::CObject::CRegistry::insert(CObject*)::" << pObject << " ID:" << pObject->mId << log::end;
    bool nSize = mObjects.size();
    // @todo: seach for nullptr in mObjects or push_back
    mObjects.push_back(pObject);
    return mObjects.size() > nSize;
  }
  
  bool CObject::CRegistry::remove(CObject* pObject) {
    log::nfo << "uix::CObject::CRegistry::remove(CObject*)::" << pObject << " ID:" << pObject->mId << log::end;
    bool nSize = mObjects.size();
    for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
      if (pObject == *it) {
        (*it) = nullptr;
      }
    }
    return mObjects.size() < nSize;
  }
  
  // public //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const int CObject::id() const { return mId; }
}}
