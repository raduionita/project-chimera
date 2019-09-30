#ifndef __cym_uix_cwidget_hpp__
#define __cym_uix_cwidget_hpp__

#include "CWindow.hpp"

namespace cym::uix { 
  class CWidget : public CWindow {
    protected:
      using CWindow::CWindow;
      using CWindow::operator=;
    protected:
      typedef CWindow super;
      static constexpr int WINDOW = CWindow::WINDOW|EWindow::CHILD;
  };
}

#endif //__cym_uix_cwidget_hpp__
