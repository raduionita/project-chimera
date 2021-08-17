#ifndef __cym_cskelet_hpp__
#define __cym_cskelet_hpp__

#include "sys/TPointer.hpp"
#include "cym/cym.hpp"

namespace cym {
  class CJoint;
  class CBone;
  class CSkeleton; 
  
  class CJoint {
    protected:
      sys::string                              mName; // @todo: maybe this should be as a NJoint{} property
      sys::spo<CJoint>                      mParent;
      std::map<sys::string, sys::spo<CJoint>> mChildren;
    public:
      CJoint(const sys::string& tName) : mName{tName}, mParent{nullptr} { }
  };
  
  class CBone {
    protected:
      sys::spo<CBone>  mParent;
      sys::spo<CJoint> mSource;
      sys::spo<CJoint> mTarget;
  };
  
  class CSkeleton {
    protected:
      sys::spo<CJoint> mRoot {new CJoint{"root"}};
    public:
      CSkeleton() {}
  };
}

#endif //__cym_cskelet_hpp__
