#ifndef __cym_uix_cobject_hpp__
#define __cym_uix_cobject_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CObject {
    class CRegistry {
      friend class CObject;
      std::vector<CObject*> mObjects;
      CRegistry();
      virtual ~CRegistry();
      bool insert(CObject*);
      bool remove(CObject*);
    };
    
    private:
    static CRegistry        sRegistry;
    
    protected:
    static std::atomic<INT> sId;
    const INT               mId = {++sId};
    
    public:
    CObject();
    virtual ~CObject();
    // move = deleted
    CObject(CObject&&) = delete;
    CObject& operator =(CObject&&) = delete;
    // copy = deleted
    CObject(const CObject&) = delete;
    CObject& operator =(const CObject&) = delete;
    // cast
    explicit operator const INT() const;
    
    public:ss
    const int id() const;
  };  
}}

#endif //__cym_uix_cobject_hpp__
