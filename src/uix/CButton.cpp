#include "uix/CButton.hpp"
#include "uix/CIcon.hpp"
#include "uix/CLayout.hpp"

namespace uix {
  CButton::CButton(CWindow* pParent, const CString& tText, const SArea& tArea/*={}*/, CIcon*&& pIcon/*=nullptr*/, uint nHints/*=WINDOW*/) : mIcon{std::move(pIcon)} {
    CYM_LOG_NFO("uix::CButton::CButton(CWindow*,CString{"<<tText<<"},SArea&,CIcon*&&,int)::" << this);
    CButton::init(pParent,tText,tArea,nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CButton::CButton(CWindow* pParent, const CString& tText, const SSize& tSize/*={}*/, CIcon*&& pIcon/*=nullptr*/, uint nHints/*=WINDOW*/) : mIcon{std::move(pIcon)} {
    CYM_LOG_NFO("uix::CButton::CButton(CWindow*,CString{"<<tText<<"},SSize&,CIcon*&&,int)::" << this);
    CButton::init(pParent,tText,SArea{tSize},nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CButton::~CButton() {
    CYM_LOG_NFO("uix::CButton::~CButton()::" << this);
    CButton::free();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CButton::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CButton::init(uint)::" << this);
  
    RETURN((mState & EState::INITED),true);

    if (pParent == nullptr) {
      ::MessageBox(NULL, "[CButton] No parent no button!", "Error", 0);
      return false;
    }
    
    mHints  = mHints | nHints | (pParent ? EWindow::VISIBLE : 0);
    mHints  = tArea == AUTO ? (mHints | EWindow::AUTOXY | EWindow::AUTOWH) : ((mHints & ~EWindow::AUTOWH) & ~EWindow::AUTOXY);
    mParent = pParent;
    mParent->assign(this);
    mTitle  = tTitle;
    mArea   = tArea;
    
    mHandle = ::CreateWindowEx(
      0,                                   // DWORD  dwExStyle
      WC_BUTTON,                           // LPCSTR lpClassName
      mTitle.c_str(),                      // LPCSTR lpWindowName
      WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_FLAT | BS_NOTIFY, // (parent), // styles: BS_OWNERDRAW
      mArea.x == AUTO ? 0             : mArea.x, 
      mArea.y == AUTO ? 0             : mArea.y, 
      mArea.w == AUTO ? CW_USEDEFAULT : mArea.w, 
      mArea.h == AUTO ? CW_USEDEFAULT : mArea.h, 
      (HWND)(*mParent),                    // HWND hWndParent // parent handle
      NULL,                                // HMENU hMenu // or (for non-top-level) attach-window id (16bit)
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
    ::SetWindowText(mHandle, mTitle.c_str());
    ::SendMessage(mHandle, CM_INIT, 0, 0);
    ::SetDefaultFont(mHandle);
    
    bool bInited = (mState = mState | EState::INITED);
    
    (mHints & EWindow::VISIBLE) && show();
  
    return bInited;
  }
  
  bool CButton::free() {
    // free only if not FREED before
    RETURN((mState & EState::FREED),true);
    // remove flag + add freed
    mState = (mState & ~EState::INITED) | EState::FREED;
    // debug after flag
    CYM_LOG_NFO("uix::CButton::free()::" << this);
    // send message to proc
    ::SendMessage(mHandle, CM_FREE, 0, 0);
    // detach from parent
    (mParent) && mParent->remove(this);
    // remove sublass
    ::RemoveWindowSubclass(mHandle, &CButton::proc, 1);
    // destroy handle
    ::DestroyWindow(mHandle);
    // just in case
    mHandle = NULL;
    // del layout
    delete mLayout;
    delete mIcon;
    // return successfuly freed 
    return mState & EState::FREED;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  LRESULT CALLBACK CButton::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR /*uSubId*/, DWORD_PTR dwRef) {
    log::dbg << "uix::CButton::proc(HWND,UINT,WPARAM,LPARAM,UINT_PTR,DWORD_PTR)" << log::end;
    switch (uMsg) {
      case WM_DESTROY: {
        CButton* pButton = reinterpret_cast<CButton*>(dwRef);
        CYM_LOG_NFO("  B::WM_DESTROY::" << pButton << " ID:" << (pButton?pButton->mId:0));
        break; 
      }
    //case WM_NCCREATE: // not fired cause ::SetWindowLongPtr is after ::CreateWindowEx
    //case WM_CREATE:   // not fired cause ::SetWindowLongPtr is after ::CreateWindowEx
    //case WM_MOUSEHOVER:
    //case WM_MOUSELEAVE: // requires ::TrackMouseEvent(TRACKMOUSEEVENT)
    //case WM_MOUSEMOVE: //
    //case WM_SETCURSOR://
      case WM_LBUTTONDOWN: {
        CButton* pButton = reinterpret_cast<CButton*>(dwRef);
        CYM_LOG_NFO("  B::WM_LBUTTONDOWN::" << pButton << " ID:" << pButton->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam));
  
        // mousedown event
        auto pEvent = new CEvent(CEvent::EType::LBUTTONDOWN, pButton);
        pEvent->mClientX  = GET_X_LPARAM(lParam);
        pEvent->mClientY  = GET_Y_LPARAM(lParam);
        pEvent->mModifier = wParam & MK_SHIFT ? EMouse::SHIFT : wParam & MK_CONTROL ? EMouse::CONTROL : EMouse::EMPTY;
        pEvent->mButton   = EMouse::LBUTTON;
        
#if UIX_EVENT_APPLICATION == UIX_ON
        bool bHandled = CApplication::instance()->handle(pEvent);
#else
        bool bHandled = pButton->handle(pEvent);
#if UIX_EVENT_PROPAGATE == UIX_ON
        bHandled = pEvent->propagate() ? CApplication::instance()->handle(pEvent) || bHandled : bHandled;
#endif // UIX_EVENT_PROPAGATE
#endif // UIX_EVENT_APPLICATION
        
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
      case WM_LBUTTONUP: { break; }
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
