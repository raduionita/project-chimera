#include "cym\uix\CButton.hpp"

namespace cym { namespace uix {
  CButton::CButton(CWindow* pParent, const CString& sText, const SArea& sArea, int nHints) {
    log::nfo << "uix::CButton::CButton()::" << this << log::end;
  }
  
  CButton::CButton(CWindow* pParent, const CString& sText, const SArea& sArea, CIcon*&&/*=nullptr*/, int nHints/*=0*/) {
    log::nfo << "uix::CButton::CButton()::" << this << log::end;
  }
  
  CButton::~CButton() {
    log::nfo << "uix::CButton::~CButton()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CButton::init(CWindow* pParent, const CString& sText, const SArea& sArea, CIcon*&&, int nHints) {
    log::nfo << "uix::CButton::init(CWindow*,CString&,SArea&,CIcon*&&,int)::" << this << log::end;
  
    RETURN(mInited,true);
  
    // set parent
    mParent = pParent;
    // add to parent's children list
    mParent && mParent->child(this);
  
    if (mParent == nullptr) {
      ::MessageBox(NULL, "[CButton] No parent no button!!", "Error", 0);
      return false;
    }
  
    mHandle = ::CreateWindowEx(
      0,                                   // DWORD  dwExStyle
      WC_BUTTON,                           // LPCSTR lpClassName
      sText.c_str(),                       // LPCSTR lpWindowName
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, // | BS_NOTIFY, // styles: BS_OWNERDRAW
      sArea.x, sArea.y,                    // int, int x, y
      sArea.w, sArea.h,                    // int, int w, h
      (HWND)(*mParent),                    // HWND hWndParent // parent handle
      NULL,                                // HMENU hMenu // or (for non-top-level) child-window id (16bit)
      NULL,/*(HINSTANCE)(*uix::app)*/      // HINSTANCE hInstance // ::GetWindowLong((HWND)(*mParent), GWL_HINSTANCE);
      this                                 // LPVOID lpParam // 
    );
  
  
    if (mHandle == NULL) {
      std::cout << "[CButton] RegisterClassEx failed!" << std::endl;
      ::MessageBox(NULL, "[CButton] CreateWindowEx failed!", "Error", 0);
      return false;
    }  // @todo trigger error event
    
    ::SetWindowLongPtr(mHandle, GWLP_WNDPROC,  (LONG_PTR)(&CButton::proc)); // (this) requires:
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
  
    ::SendMessage(mHandle, CM_INIT, 0, 0);
  
    ::SetDefaultFont(mHandle);
  
    return mInited;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  LRESULT CButton::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
  
    return ::CallWindowProc(CWindow::proc, hWnd,  uMsg, wParam, lParam); // at the end of CButton::proc()
  }
}}

// group box
  // BS_GROUPBOX (eye candy) before 1st radio
  // WS_GROUP (on the first radio button)
  // WS_CHILD | WS_VISIBLE (all radios)
  // BS_AUTORADIOBUTTON
  // BS_AUTOCHECKBOX
  // (HMENU)(IDC_CHK123..)
  // hWnd parent on all
  // WS_GROUP (to start a second group)
