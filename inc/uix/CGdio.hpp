#ifndef __uix_cgdio_hpp__
#define __uix_cgdio_hpp__

#include "CObject.hpp"

namespace uix {
  template <typename T>
  class CGdio : public CObject {
    protected:
      mutable bool mInited {false}; // allow update inside const methods
      mutable T    mHandle {NULL};
    public: // ctor
      CGdio(T hHandle = NULL) : mHandle{hHandle} { }
      ~CGdio() { free(); }
    public: // cast
      explicit operator T() { if (!mInited) mInited = init(); return mHandle; }
    protected:
      virtual bool init() = 0;
              bool free() { return ::DeleteObject(mHandle) != FALSE; }
    public:
              bool null() const { return mInited == true && mHandle == T(NULL); }
  };
}

#endif //__uix_cgdio_hpp__
