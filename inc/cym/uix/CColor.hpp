#ifndef __cym_uix_ccolor_hpp__
#define __cym_uix_ccolor_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CColor { // demote to SColor
    public:
      union {
        COLORREF rgb; 
        struct { BYTE r; BYTE g; BYTE b; BYTE a; };
      };
    public: // ctor
      CColor(COLORREF rgb = 0) : rgb(rgb) { }
      CColor(BYTE r, BYTE g, BYTE b, BYTE a = 0) : rgb(RGB(r, g, b)) { }
    public: // cast
      operator       COLORREF()       { return rgb; }
      operator const COLORREF() const { return rgb; }
  };
}}

#endif // __cym_uix_ccolor_hpp__
