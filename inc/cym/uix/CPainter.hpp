#ifndef __cym_uix_cpainter_hpp__
#define __cym_uix_cpainter_hpp__

#include "CObject.hpp"
#include "CWindow.hpp"

// @todo: use CWindow* style & DC

namespace cym { namespace uix {
  enum class EShape : int {
      NONE = 0,
      ARC  = 1,
  };
  
  class CPainter : public CObject {
    public:
      CPainter(CWindow* pWindow);
      ~CPainter();
    public:
      bool palette(CPalette*);
      bool clear();
      bool arc();
      bool circle();
      bool ellipse();
      bool bitmap();
      bool icon();
      bool label();
      bool text();
      bool point();
      bool line();
      bool spline();
      bool polygon();
      bool rectangle();
      bool squircle(); // rounded rectangle
      bool gradient(); // rectangle filled w/ a gradient
  };
}}

#endif //__cym_uix_cpainter_hpp__
