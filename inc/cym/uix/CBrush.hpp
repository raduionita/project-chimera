#ifndef __cym_uix_cbrush_hpp__
#define __cym_uix_cbrush_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CBrush : public CObject {
    protected:
      enum EType {
        SOLID   = 1,
        HATCH   = 2,
        PATTERN = 3,
      };
    protected:
      HBRUSH   mHandle;
      EType    mType;
    public: // ctor
      CBrush();
      ~CBrush();
    public: // cast
      explicit operator       HBRUSH();
      explicit operator const HBRUSH() const;
  };
}}

#endif //__cym_uix_cbrush_hpp__
