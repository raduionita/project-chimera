#ifndef __cym_uix_cpainter_hpp__
#define __cym_uix_cpainter_hpp__

#include "CObject.hpp"
#include "CWindow.hpp"

namespace cym { namespace uix {
  class CPainter : public CObject {
    public:
      CPainter(CWindow* pWindow);
      ~CPainter();
    public:
      void palette(CPalette*);
      void clear();
      void arc();
      void circle();
      void ellipse();
      void bitmap();
      void icon();
      void label();
      void text();
      void point();
      void line();
      void spline();
      void polygon();
      void rectangle();
      void squircle(); // rounded rectangle
      void gradient(); // rectangle filled w/ a gradient
      
  };
}}

#endif //__cym_uix_cpainter_hpp__
