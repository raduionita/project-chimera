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
      CObject(const CObject&);
      CObject& operator =(const CObject&);
      operator const INT() const;
    public:
      const int getId() const;
  };  
}}

#endif //__cym_uix_cobject_hpp__
