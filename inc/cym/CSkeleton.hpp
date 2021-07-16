#ifndef __cym_cskelet_hpp__
#define __cym_cskelet_hpp__

#include "sys/CPointer.hpp"
#include "cym/cym.hpp"

namespace cym {
  class CJoint;
  class CBone;
  class CSkeleton; 
  
  class CJoint {
    protected:
      cym::name                              mName; // @todo: maybe this should be as a NJoint{} property
      sys::sptr<CJoint>                      mParent;
      std::map<cym::name, sys::sptr<CJoint>> mChildren;
    public:
      CJoint(const cym::name& tName) : mName{tName}, mParent{nullptr} { }
  };
  
  class CBone {
    protected:
      sys::sptr<CBone>  mParent;
      sys::sptr<CJoint> mSource;
      sys::sptr<CJoint> mTarget;
  };
  
  class CSkeleton {
    protected:
      sys::sptr<CJoint> mRoot {new CJoint{"root"}};
    public:
      CSkeleton() {}
  };
}

#endif //__cym_cskelet_hpp__
