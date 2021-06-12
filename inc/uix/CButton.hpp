#ifndef __uix_cbutton_hpp__
#define __uix_cbutton_hpp__

#include "uix/uix.hpp"
#include "uix/CControl.hpp"

namespace uix {
  class CButton : public CControl {
    protected:
      using CControl::CControl;
      using CControl::operator=;
      typedef CControl super;
      static constexpr int WINDOW = CControl::WINDOW;
    protected:
      CIcon* mIcon {nullptr};
    private:
      CButton() = default;
    public:
      CButton(CWindow*, const CString&, const SArea&, CIcon*&& = nullptr, uint=WINDOW);
      ~CButton();
    protected:
      virtual bool init(CWindow* = nullptr, const CString& = "", const SArea& = AUTO, uint = WINDOW) override;
      virtual bool free() override;
    protected:
      static LRESULT CALLBACK proc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);
  };
}

#endif //__uix_cbutton_hpp__
