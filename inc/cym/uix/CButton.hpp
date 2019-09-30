#ifndef __cym_uix_cbutton_hpp__
#define __cym_uix_cbutton_hpp__

#include "CControl.hpp"

namespace cym { namespace uix {
  class CButton : public CControl {
    protected:
      using CControl::CControl;
      using CControl::operator=;
      typedef CControl super;
      static constexpr int WINDOW = CControl::WINDOW;
    public:
      CButton(CWindow*, const CString&, const SArea&,                     int);
      CButton(CWindow*, const CString&, const SArea&, CIcon*&& = nullptr, int = ZERO);
      ~CButton();
    protected:
      bool init(CWindow*, const CString&, const SArea&, CIcon*&&, int);
    protected:
      static LRESULT CALLBACK proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
  };
}}

#endif //__cym_uix_cbutton_hpp__
