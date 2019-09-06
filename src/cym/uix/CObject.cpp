#include "cym/uix/CObject.hpp"

namespace cym { namespace uix {
  std::atomic<INT>   CObject::sId{0};
  CObject::CRegistry CObject::sRegistry;
  
  CObject::CObject() : mId{++sId} {
    std::cout << "uix::CObject::CObject()::" << this << " ID:" << mId << std::endl;
    mId && sRegistry.insert(this); // only if it has a valid mId
  }
  
  CObject::~CObject() {
    std::cout << "uix::CObject::~CObject()::" << this << " ID:" << mId << std::endl;
    mId && sRegistry.remove(this); // only if it has a valid mId
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::operator const INT() const {
    return mId;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CObject::CRegistry::CRegistry() {
    std::cout << "uix::CObject::CRegistry::CRegistry()::" << this << std::endl;
  }
  
  CObject::CRegistry::~CRegistry() {
    std::cout << "uix::CObject::CRegistry::~CRegistry()::" << this << std::endl;
    for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
      if (*it) {
        delete (*it);
      }
    }
  }
  
  bool CObject::CRegistry::insert(CObject* pObject) {
    std::cout << "uix::CObject::CRegistry::insert(CObject*)::" << pObject << " ID:" << pObject->mId << std::endl;
    bool nSize = mObjects.size();
    // @todo: seach for nullptr in mObjects or push_back
    mObjects.push_back(pObject);
    return mObjects.size() > nSize;
  }
  
  bool CObject::CRegistry::remove(CObject* pObject) {
    std::cout << "uix::CObject::CRegistry::remove(CObject*)::" << pObject << " ID:" << pObject->mId << std::endl;
    bool nSize = mObjects.size();
    for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
      if (pObject == *it) {
        (*it) = nullptr;
      }
    }
    return mObjects.size() < nSize;
  }
  
  // public //////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  inline const int CObject::id() const { return mId; }
}}
