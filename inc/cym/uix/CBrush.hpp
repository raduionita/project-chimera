#ifndef __cym_uix_cbrush_hpp__
#define __cym_uix_cbrush_hpp__

#include "CObject.hpp"
#include "CColor.hpp"

namespace cym { namespace uix {
  class CBrush : public CObject {
    protected:
      enum EType {
        SOLID   = 1,
        HATCH   = 2,
        PATTERN = 3,
      };
    protected:
      HBRUSH   mHandle {HBRUSH(NULL_BRUSH)};
      EType    mType   {EType::SOLID};
    public: // ctor
      CBrush();
      CBrush(const CColor&);
      CBrush(const CColor&, int);
      CBrush(const CBitmap&);
      ~CBrush();
    public: // cast
      explicit operator       HBRUSH();
      explicit operator const HBRUSH() const;
    protected:
      
  };
}}

#endif //__cym_uix_cbrush_hpp__
