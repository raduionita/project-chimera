#ifndef __cym_cskelet_hpp__
#define __cym_cskelet_hpp__

#include "sys/CPointer.hpp"
#include "cym/cym.hpp"

namespace cym {
  class CJoint;  typedef sys::sptr<CJoint>  PJoint;
  class CBone;   typedef sys::sptr<CBone>   PBone;
  class CSkelet; typedef sys::sptr<CSkelet> PSkelet;
  
  class CJoint {
    protected:
      uint        mID;
      sys::string mName; // @todo: maybe this should be as a NJoint{} property
      PJoint      mParent;
  };
  
  class CBone {
    protected:
      PBone  mParent;
      PJoint mSource;
      PJoint mTarget;
  };
  
  class CSkelet {
    protected:
      PJoint mRoot;
  };
}

#endif //__cym_cskelet_hpp__
