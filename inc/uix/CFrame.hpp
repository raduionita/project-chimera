#ifndef __uix_cframe_hpp__
#define __uix_cframe_hpp__

#include "uix/uix.hpp"
#include "uix/CPopup.hpp"

namespace uix {
  class CFrame : public CPopup {
      friend class CCanvas;
    protected:
      using CPopup::CPopup;
      using CPopup::operator=;
    protected:
      typedef CPopup super;
      static constexpr int WINDOW = CPopup::WINDOW|EWindow::BORDER|EWindow::TITLE|EWindow::FRAME|EWindow::SYSBOX|EWindow::MINBOX|EWindow::MAXBOX|EWindow::SIZER;
    private:
      CFrame() = default;
    public:
      CFrame(                          uint);
      CFrame(CWindow*,                 uint=WINDOW);
      CFrame(CWindow*, const CString&, uint=WINDOW);
      ~CFrame();
    protected:
      virtual bool init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = WINDOW) override;
  };
}

#endif //__uix_cframe_hpp__
