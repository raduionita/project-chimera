#ifndef __cym_uix_cobject_hpp__
#define __cym_uix_cobject_hpp__

#include "uix.hpp"

namespace cym::uix {
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
    public: // ctor
      CObject();
      virtual ~CObject();
    public: // move = deleted
      CObject(CObject&&) = delete;
      CObject& operator =(CObject&&) = delete;
    public: // copy = deleted
      CObject(const CObject&) = delete;
      CObject& operator =(const CObject&) = delete;
    public: // cast
      explicit operator const INT() const;
    public:
      const int id() const;
  };
}

#endif //__cym_uix_cobject_hpp__
