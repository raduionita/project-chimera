#ifndef __cym_uix_cgdio_hpp__
#define __cym_uix_cgdio_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  template <typename T>
  class CGdio : public CObject {
    protected:
      T mHandle {NULL};
    public: // ctor
      CGdio(T hHandle = NULL) : mHandle{hHandle} { }
      ~CGdio() { free(); }
    public: // cast
      explicit operator T() { if (mHandle == NULL) init(); return mHandle; }
    protected:
      virtual bool init() = 0;
    public:
      virtual bool free() { return ::DeleteObject(mHandle) != FALSE; }
              bool empty() { return mHandle == NULL; }
  };
}}

#endif //__cym_uix_cgdio_hpp__
