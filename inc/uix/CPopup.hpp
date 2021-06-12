#ifndef __uix_cpopup_hpp__
#define __uix_cpopup_hpp__

#include "CWindow.hpp"

namespace uix {
  class CPopup : public CWindow {
      friend class CFrame;
      friend class CDialog;
    protected:
      using CWindow::CWindow;
      using CWindow::operator=;
      typedef CWindow super;
      static constexpr int WINDOW = CWindow::WINDOW|EWindow::POPUP;
    public:
      virtual bool fullscreen(uint = EFullscreen::FULLSCREEN|EFullscreen::CURSOR);
  };
}

#endif //__uix_cpopup_hpp__
