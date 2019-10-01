#include "cym\uix\CButton.hpp"

namespace cym::uix {
  CButton::CButton(CWindow* pParent, const CString& sText, const SArea& sArea, int nHints) {
    log::nfo << "uix::CButton::CButton(CWindow*,CString&,SArea&,int)::" << this << log::end;
    init(pParent,sText,sArea,nullptr,nHints);
  }
  
  CButton::CButton(CWindow* pParent, const CString& sText, const SArea& sArea, CIcon*&& pIcon/*=nullptr*/, int nHints/*=0*/) {
    log::nfo << "uix::CButton::CButton(CWindow*,CString&,SArea&,CIcon*&&,int)::" << this << log::end;
    init(pParent,sText,sArea,std::move(pIcon),nHints);
  }
  
  CButton::~CButton() {
    log::nfo << "uix::CButton::~CButton()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CButton::init(CWindow* pParent, const CString& sText, const SArea& sArea, CIcon*&&, int/*nHints*/) {
    log::nfo << "uix::CButton::init(CWindow*,CString&,SArea&,CIcon*&&,int)::" << this << log::end;
  
    RETURN(mInited,true);
    
    if (pParent == nullptr) {
      ::MessageBox(NULL, "[CButton] No parent no button!!", "Error", 0);
      return false;
    }
  
    // set parent // add to parent's children list
    (mParent = pParent) && (mParent->child(this));
  
    mHandle = ::CreateWindowEx(
      0,                                   // DWORD  dwExStyle
      WC_BUTTON,                           // LPCSTR lpClassName
      sText.c_str(),                       // LPCSTR lpWindowName
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT | BS_NOTIFY, // (parent), // styles: BS_OWNERDRAW
      sArea.x, sArea.y,                    // int, int x, y
      sArea.w, sArea.h,                    // int, int w, h
      (HWND)(*mParent),                    // HWND hWndParent // parent handle
      NULL,                                // HMENU hMenu // or (for non-top-level) child-window id (16bit)
      (HINSTANCE)(*mApplication),          // HINSTANCE hInstance // ::GetWindowLong((HWND)(*mParent), GWL_HINSTANCE);
      this                                 // LPVOID lpParam // 
    );
  
    if (mHandle == NULL) {
      std::cout << "[CButton] RegisterClassEx failed!" << std::endl;
      ::MessageBox(NULL, "[CButton] CreateWindowEx failed!", "Error", 0);
      return false;
    }  // @todo trigger error event
    
    ::SetWindowSubclass(mHandle, &CButton::proc, 1, DWORD_PTR(this));
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
    ::SetWindowText(mHandle, sText.c_str());
    ::SendMessage(mHandle, CM_INIT, 0, 0);
    ::SetDefaultFont(mHandle);
  
    return mInited;
  }
  
  bool CButton::free() {
    log::nfo << "uix::CButton::free()::" << this << log::end;
    // remove sublass
    ::RemoveWindowSubclass(mHandle, &CButton::proc, 1);
    // free window
    return super::free();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  LRESULT CALLBACK CButton::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR /*uSubId*/, DWORD_PTR dwRef) {
    log::dbg << "uix::CButton::proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR)" << log::end;
    switch (uMsg) {
      case WM_DESTROY: {
        log::nfo << "   B:WM_DESTROY" << log::end;
        break; 
      }
      //case WM_NCCREATE: // not fired cause ::SetWindowLongPtr is after ::CreateWindowEx
      //case WM_CREATE:   // not fired cause ::SetWindowLongPtr is after ::CreateWindowEx
      //case WM_MOUSEHOVER:
      //case WM_MOUSELEAVE: // requires ::TrackMouseEvent(TRACKMOUSEEVENT)
      // case WM_MOUSEMOVE: //
      //case WM_SETCURSOR://
      case WM_LBUTTONDOWN: {
        CButton* pButton = reinterpret_cast<CButton*>(dwRef);
        log::nfo << "   B:WM_LBUTTONDOWN::" << pButton << " ID:" << pButton->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam) << log::end;
  
        // mousedown event
        auto pEvent = new CEvent(EEvent::LBUTTONDOWN, pButton);
        pEvent->mClientX  = GET_X_LPARAM(lParam);
        pEvent->mClientY  = GET_Y_LPARAM(lParam);
        pEvent->mModifier = wParam;
        pEvent->mButton   = EMouse::LBUTTON;
        
        bool bHandled = pButton->handle(pEvent);
        bHandled = pEvent->propagate() ? CApplication::instance()->handle(pEvent) || bHandled : bHandled;
        
        DELETE(pEvent);
        
        // wParam: 0x0001 MK_LBUTTON
        //         0x0002 MK_RBUTTON  (virtual keys)
        //         0x0004 MK_SHIFT
        //         0x0008 MK_CONTROL
        //         0x0010 MK_MBUTTON
        //         0x0020 MK_XBUTTON1
        //         0x0040 MK_XBUTTON2
        // problematic w/ multiple monitors
        // GET_X_LPARAM(lParam): x mouse position (reltive to the upper left conner of the client area)
        // GET_Y_LPARAM(lParam): y mouse position
        break; // if handled (return 0) => not clicked animation
      }
      case WM_LBUTTONUP: {
        CButton* pButton = reinterpret_cast<CButton*>(dwRef);
        log::nfo << "   B:WM_LBUTTONUP::" << pButton << " ID:" << pButton->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam) << log::end;
        
        
        break; // if handled (return 0) => NO WM_COMMAND
      }
      //case WM_ERASEBKGND://
      //case WM_NCPAINT://
      //case WM_PAINT: //
    }
    return ::DefSubclassProc(hWnd,uMsg,wParam,lParam);
  }
}

// group box
  // BS_GROUPBOX (eye candy) before 1st radio
  // WS_GROUP (on the first radio button)
  // WS_CHILD | WS_VISIBLE (all radios)
  // BS_AUTORADIOBUTTON
  // BS_AUTOCHECKBOX
  // (HMENU)(IDC_CHK123..)
  // hWnd parent on all
  // WS_GROUP (to start a second group)
  
  
// image/icon
  // icon        // BM_SETIMAGE + (BS_ICON or BS_BITMAP)
  // icon + text // BM_SETIMAGE
