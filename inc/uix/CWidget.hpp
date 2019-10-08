#ifndef __uix_cwidget_hpp__
#define __uix_cwidget_hpp__

#include "CWindow.hpp"

namespace uix { 
  class CWidget : public CWindow {
    protected:
      using CWindow::CWindow;
      using CWindow::operator=;
    protected:
      typedef CWindow super;
      static constexpr int WINDOW = CWindow::WINDOW|EWindow::CHILD;
  };
}

#endif //__uix_cwidget_hpp__
