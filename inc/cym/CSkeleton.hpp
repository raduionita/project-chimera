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
      sys::ptr<CJoint>                      mParent;
      std::map<sys::string, sys::ptr<CJoint>> mChildren;
    public:
      CJoint(const sys::string& tName) : mName{tName}, mParent{nullptr} { }
  };
  
  class CBone {
    protected:
      sys::ptr<CBone>  mParent;
      sys::ptr<CJoint> mSource;
      sys::ptr<CJoint> mTarget;
  };
  
  class CSkeleton {
    protected:
      sys::ptr<CJoint> mRoot {new CJoint{"root"}};
    public:
      CSkeleton() {}
  };
}

#endif //__cym_cskelet_hpp__
