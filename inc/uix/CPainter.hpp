#ifndef __uix_cpainter_hpp__
#define __uix_cpainter_hpp__

#include "CObject.hpp"
#include "CWindow.hpp"

// @todo: use CWindow* style & DC

namespace uix {
  enum class EPainter : int {
      NONE = ZERO,
      FILL =  0b1,
  };
  
  enum class EShape : int {
      NONE = 0,
      ARC  = 1,
  };
  
  class CPainter : public CObject {
    protected:
      CWindow* mWindow {nullptr};
    public:
      CPainter(CWindow*);
      ~CPainter();
    public: // tools
      bool palette(CPalette*&&); // @todo: defaults to null
      bool pen(CPen*&&);         // @todo: defaults to null
    public: // actions
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
      bool rectangle(const SArea&, const EPainter& = EPainter::NONE);
      bool squircle(); // rounded rectangle
      bool gradient(); // rectangle filled w/ a gradient
  };
}

#endif //__uix_cpainter_hpp__
