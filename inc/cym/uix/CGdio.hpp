#ifndef __cym_uix_cgdio_hpp__
#define __cym_uix_cgdio_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  template <typename T>
  class CGdio : public CObject {
    protected:
      bool mInited {false};
      T    mHandle {NULL};
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
}}

#endif //__cym_uix_cgdio_hpp__
