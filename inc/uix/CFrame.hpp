#ifndef __uix_cframe_hpp__
#define __uix_cframe_hpp__

#include "CPopup.hpp"

namespace uix {
  class CFrame : public CPopup {
    protected:
      using CPopup::CPopup;
      using CPopup::operator=;
    protected:
      typedef CWindow super;
      static constexpr int WINDOW = CPopup::WINDOW|EWindow::BORDER|EWindow::TITLE|EWindow::FRAME|EWindow::SYSBOX|EWindow::MINBOX|EWindow::MAXBOX|EWindow::SIZER;
    public:
      CFrame(          int = ZERO);
      CFrame(CWindow*, int = ZERO);
      ~CFrame();
    protected:
      virtual bool init(CWindow*, int) override;
  };
}

#endif //__uix_cframe_hpp__
