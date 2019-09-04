#ifndef __cym_uix_cpopup_hpp__
#define __cym_uix_cpopup_hpp__

#include "CWindow.hpp"

namespace cym { namespace uix {
  class CPopup : public CWindow {
    protected:
      using CWindow::CWindow;
      typedef CWindow super;
      static constexpr int STYLE = CWindow::STYLE|EHint::POPUP;
  };
}}

#endif //__cym_uix_cpopup_hpp__
