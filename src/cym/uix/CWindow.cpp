#include "cym/uix/CWindow.hpp"
#include "cym/uix/CLayout.hpp"

namespace cym { namespace uix {
  CWindow::CWindow() {
    log::nfo << "uix::CWindow::CWindow()::" << this << log::end;
  }
  
  CWindow::~CWindow() {
    log::nfo << "uix::CWindow::~CWindow()::" << this << log::end;
    // release
    free();
  }
  
  inline int operator &(const CWindow::SState& sState, const EState& eState) {
    return sState.eState & eState;
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CWindow::operator HWND() {
    log::nfo << "uix::CWindow::operator HWND()::" << this << log::end;
    return mHandle;
  }
  
  CWindow::operator const HWND() const {
    log::nfo << "uix::CWindow::operator HWND()::" << this << log::end;
    return mHandle;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CWindow::init(CWindow* pParent, int nHints) {
    log::nfo << "uix::CWindow::init(CWindow*,int)::" << this << " NAME:" << name() << log::end;
    
    // set parent
    mParent = pParent;
    // add to parent's children list
    mParent && mParent->child(this);
  
    WNDCLASSEX sWndCls = {
      sizeof(WNDCLASSEX),                       // UINT      // cbSize        // struct size  
      CS_HREDRAW|CS_VREDRAW|CS_OWNDC,           // UINT      // style
      CWindow::proc,                            // WNDPROC   // lpfnWndProc   // uix::CWidget::proc
      0,                                        // int       // cbClsExtra    // no extra bytes after the window class
      0,                                        // int       // cbWndExtra    // extra bytes to allocate after the win instance 
      (HINSTANCE)(*CApplication::instance()),// HINSTANCE // hInstance     // to identify the dll that loads this module  
      ::LoadIcon(NULL, IDI_APPLICATION),        // HICON     // hIcon
      ::LoadCursor(NULL, IDC_ARROW),            // HCURSOR   // hCursor
      (HBRUSH)(NULL_BRUSH),                     // HBRUSH    // hbrBackground
      NULL,                                     // LPCTSTR   // lpszMenuName  // no menu
      name().c_str(),                           // LPCTSTR   // lpszClassName
      ::LoadIcon(NULL, IDI_APPLICATION)         // HICON     // hIconSm
    };
  
    if (!::RegisterClassEx(&sWndCls)) {
      log::nfo << "[CWindow] ::RegisterClassEx() failed!" << log::end;
      ::MessageBox(NULL, "[CWindow] ::RegisterClassEx() failed!", "ERROR", MB_OK);
      return false;
    }
  
    DWORD dwExStyle = 0; // WS_EX_APPWINDOW;
    DWORD dwStyle   = 0;
  
    dwStyle |= nHints & EHint::POPUP    ? WS_POPUP                   : 0;
    dwStyle |= nHints & EHint::CHILD    ? WS_CHILD                   : 0;
    dwStyle |= nHints & EHint::MAXBOX   ? WS_MAXIMIZEBOX             : 0;
    dwStyle |= nHints & EHint::MINBOX   ? WS_MINIMIZEBOX             : 0;
    dwStyle |= nHints & EHint::SYSBOX   ? WS_SYSMENU                 : 0;
    dwStyle |= nHints & EHint::FRAME    ? WS_THICKFRAME | WS_SIZEBOX : 0;
    dwStyle |= nHints & EHint::TITLE    ? WS_CAPTION                 : 0;
    dwStyle |= nHints & EHint::BORDER   ? WS_BORDER                  : 0;
    dwStyle |= nHints & EHint::VISIBLE  ? WS_VISIBLE                 : 0;
    dwStyle |= nHints & EHint::DISABLED ? WS_DISABLED                : 0;
    dwStyle |= nHints & EHint::HSCROLL  ? WS_HSCROLL                 : 0;
    dwStyle |= nHints & EHint::VSCROLL  ? WS_VSCROLL                 : 0;
    dwStyle |= nHints & EHint::MINIMIZE ? WS_MINIMIZE                : 0;
    dwStyle |= nHints & EHint::MAXIMIZE ? WS_MAXIMIZE                : 0;
    dwStyle |= nHints & EHint::NOCLIP   ? 0                          : WS_CLIPSIBLINGS;
    dwStyle |= nHints & EHint::NOCLIP   ? 0                          : WS_CLIPCHILDREN;
  
    mHandle = ::CreateWindowEx(
      dwExStyle,                                 // DWORD     // dwExStyle    // ex. style (0 = default)
      name().c_str(),                            // LPCSTR    // lpClassName  // window class name
      name().c_str(),                            // LPCSTR    // lpWindowName // window title name
      dwStyle,                                   // DWORD     // dwExStyle    // style
      CW_USEDEFAULT, CW_USEDEFAULT,              // int       // x, y 
      CW_USEDEFAULT, CW_USEDEFAULT,              // int       // width, height
      mParent ? (HWND)(*mParent) : NULL,         // HWND      // hWndParent   // parent handle
      NULL,                                      // HMENU     // hMenu        // menu handle
      (HINSTANCE)(*CApplication::instance()), // HINSTANCE // hInstance    //  application handle
      this                                       // LPVOID    // lpParam      // additional app data (@see WM_CREATE & CREATESTRUCT)
    );
  
    if (!mHandle) {
      ::MessageBox(NULL, "[CWindow] ::CreateWindowEx() failed!", "ERROR", MB_OK);
      log::nfo << "[CWindow] ::CreateWindowEx() failed!" << log::end;
      return false;
    }
  
    // add class pointer to handle's user-data // @see CWindow::proc() 
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
  
    // reset default window styles // requires SetWindowPos + SWP_FRAMECHANGED
    ::SetWindowLong(mHandle, GWL_STYLE,   dwStyle);
    ::SetWindowLong(mHandle, GWL_EXSTYLE, dwExStyle);
    ::SetWindowPos(mHandle, NULL, 0,0,0,0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
  
    ::SendMessage(mHandle, CM_INIT, 0, 0);
    
    return (mInited = true);
  }
  
  bool CWindow::free() {
    log::nfo << "uix::CWindow::free()::" << this << log::end;
    // delete children
    for (CWindow*& pChild : mChildren) {
      DELETE(pChild);
    }
    // remove from parent
    if (mParent != nullptr) {
      mParent->mChildren.erase(std::remove(mParent->mChildren.begin(), mParent->mChildren.end(), this), mParent->mChildren.end());
    }
    // release 
    ::ReleaseDC(mHandle, ::GetDC(mHandle));
    // delete handle
    ::DestroyWindow(mHandle);
    // unregister name class
    ::UnregisterClass(name().c_str(), (HINSTANCE)(*CApplication::instance()));
    // clear
    mHandle = NULL;
    mInited = false;
    return !mInited;
  }
  
  inline CString CWindow::name() const { return cym::concat("uix::CWindow::", mId); }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  bool CWindow::show(int nHints/*=1*/) {
    log::nfo << "uix::CWindow::show()::" << this << log::end;
    // @todo:   0b = hide
    // @todo:  01b = show | make visible
    // @todo:  10b = 2 = maximize
    return mInited && ::ShowWindow(mHandle, SW_SHOW);
  }
  
  bool CWindow::hide(int nHints/*=1*/) {
    log::nfo << "uix::CWindow::hide()::" << this << log::end;
    // @todo:   0b = show
    // @todo:   1b = hide | make invisible
    // @todo:  01b = 2 = minimize
    return mInited && ::ShowWindow(mHandle, SW_HIDE);
  }
  
  bool CWindow::focus(int nHints/*=1*/) {
    log::nfo << "uix::CWindow::focus()::" << this << log::end;
    ::SetFocus(mHandle); // returns window w/ previous focus
    return true;
  }
  
  bool CWindow::move(int x, int y) {
    log::nfo << "uix::CWindow::move("<< x <<","<< y <<")::" << this << log::end;
  
    RETURN(!mInited, false);
    
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
    
    x = x == AUTO ? 0 : x;
    y = y == AUTO ? 0 : y;
    
    RECT sRect = {x, y, 0, 0};
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);

    x = sRect.left; // @todo: +1 issue 'cause of border 
    // y = y;
    
    return !(mStates[SState::CURR] & EState::MAXIMIZED) && !(mStates[SState::CURR] & EState::FULLSCREEN)
        && (::SetWindowPos(mHandle, NULL, x, y, 0, 0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE));
  }
  
  bool CWindow::size(int w, int h) {
    log::nfo << "uix::CWindow::size("<< w <<","<< h <<")::" << this << log::end;
  
    RETURN(!mInited, false);
    
    HWND hWindow = mHandle;
    HWND hParent = mParent ? mParent->mHandle : ::GetDesktopWindow();
  
    RECT sPRect = {0};
    ::GetClientRect(hParent, &sPRect);
    
    w = w == AUTO ? sPRect.right  - sPRect.left : w;
    h = h == AUTO ? sPRect.bottom - sPRect.top  : h;
    
    DWORD dwExStyle = (DWORD)::GetWindowLong(hWindow, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(hWindow, GWL_STYLE);
    
    RECT sWRect = {0, 0, w, h};
    ::AdjustWindowRectEx(&sWRect, dwStyle, FALSE, dwExStyle);
    
    w = sWRect.right - sWRect.left;
    h = sWRect.bottom - sWRect.top;
    
    return !(mStates[SState::CURR] & EState::MAXIMIZED) && !(mStates[SState::CURR] & EState::FULLSCREEN)
        && (::SetWindowPos(hWindow, NULL, 0, 0, w, h, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE));
  }
  
  bool CWindow::center() {
    log::nfo << "uix::CWindow::center()::" << this << log::end;
    
    RETURN(!mInited, false);
    
    HWND  hParent = mParent == nullptr ? ::GetDesktopWindow() : mParent->mHandle;
    HWND& hWindow = mHandle;
    
    RECT sPRect, sWRect;
    
    ::GetClientRect(hParent, &sPRect); // client coords (no header)
    ::GetClientRect(hWindow, &sWRect);
  
    return move((sPRect.right - sWRect.right)/2, (sPRect.bottom - sWRect.bottom)/2);
  
    // SRect sRect;
    // ::SystemParametersInfo(SPI_GETWORKAREA, 0, &sRect, 0);
    // x = (sRect.r - w) / 2;
    // y = (sRect.b - h) / 2;
  }
  
  SRect CWindow::adjust() {
    log::nfo << "uix::CWindow::adjust()::" << this << log::end;
    
    RETURN(!mInited, {});
  
    // need the styles for correct window shape adjustment
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
  
    RECT sRect;
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);
    
    return {sRect.left, sRect.top, sRect.right, sRect.bottom};
  }

  bool CWindow::maximize() {
    log::nfo << "uix::CWindow::maximize()::" << this << log::end;
    return /*(mState |= EState::MAXIMIZED) &&*/ ::ShowWindow(mHandle, SW_MAXIMIZE);
  }
  
  bool CWindow::minimize() {
    log::nfo << "uix::CWindow::minimize()::" << this << log::end;
    return /*(mState |= EState::MINIMIZED) &&*/ ::ShowWindow(mHandle, SW_MINIMIZE);
  }
  
  bool CWindow::fullscreen(int) {
    log::nfo << "uix::CWindow::fullscreen()::" << this << log::end;
    return false;
  }
  
  CWindow::SState CWindow::state(int what/*=SState::CURR*/) const {
    assert(SState::PREV <= what && what <= SState::NEXT && "CWindow::mStates[what] out of bounds!");
    return mStates[what];
  }
  
  bool CWindow::area(const SArea& sArea) {
    return move(sArea.x,sArea.y) && size(sArea.w, sArea.h);
  }
  
  SArea CWindow::area() const {
    RECT sRect;
    ::GetClientRect(mHandle, &sRect);
    return {sRect.left,sRect.top,sRect.right-sRect.left,sRect.bottom-sRect.top};
  }
  
  auto CWindow::layout() const -> decltype(mLayout) {
    return mLayout;
  }
  
  auto CWindow::layout(CLayout* pLayout) -> decltype(mLayout) {
    mLayout = pLayout;
    mLayout->layout(this);
    return mLayout;
  }
  
  bool CWindow::child(CWindow* pChild) {
    mChildren.push_back(pChild);
    return true;
  }
  
  auto CWindow::parent() const -> decltype(mParent) {
    return mParent;
  }
  
  auto CWindow::children() const -> decltype(mChildren) {
    return mChildren;
  }
  
  auto CWindow::siblings() const -> decltype(mChildren) {
    decltype(mParent->mChildren) aSiblings;
    // 1 beause if parent has only 1 child then I am it
    if (mParent != nullptr && mParent->mChildren.size() > 1) {
      aSiblings.reserve(mParent->mChildren.size()-1);
      decltype(mParent->mChildren)::size_type nPos = 0;
      // for each parent's child
      for (auto it = mParent->mChildren.begin(); it != mParent->mChildren.end(); ++it) {
        // skip me
        if (*it != this) {
          // add sibling
          aSiblings[nPos] = *it;
        }
        nPos++;
      }
    }
    return aSiblings;
  }
  
  bool CWindow::title(const CString& sTitle) {
    return ::SetWindowText(mHandle, sTitle.c_str());
  }
    
  CString CWindow::title() const {
    CHAR szTitle[256];
    ::GetWindowTextA(mHandle, szTitle, 256);
    return CString(szTitle);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CWindow* CWindow::find(const CString& name) {
    log::nfo << "uix::CWindow::find(" << name << ")::" << log::end;
    HWND hWnd = ::FindWindow(NULL, name.c_str());
    return reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
  }
  
  LRESULT CWindow::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
      case WM_NCCREATE: { break; }
      case WM_CREATE: {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        CWindow*      pWindow = reinterpret_cast<CWindow*>(pCreate->lpCreateParams);
        BREAK(!pWindow);
        log::nfo << "   W:WM_CREATE::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << log::end;
        // @todo: create event
        break; 
      }
      case WM_NOTIFY: { break; }
      case WM_INITDIALOG: { break; }
      case CM_INIT: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:CM_INIT::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << log::end;
        return 0;
      }
      case CM_STATE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:CM_STATE::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << log::end;
        return 0;
      }
      case WM_CLOSE: { // called on [x] or window menu [Close] // triggers: WM_DESTROY
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:WM_CLOSE::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << log::end;
        // @todo: close event
        ::PostQuitMessage(0);
        break;
      }
      case WM_ACTIVATE: { break; }
      case WM_DESTROY: { break; }
      case WM_SETFOCUS: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:WM_SETFOCUS::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << log::end;
        // @todo: focus event
        break; 
      }
      case WM_KILLFOCUS: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:WM_KILLFOCUS::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << log::end;
        // @todo: blur event
        break; 
      }
      case WM_SHOWWINDOW: { break; }
      case WM_DRAWITEM: { break; }
      case WM_COMMAND: { break; }
      case WM_MOVE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:WM_MOVE::" << pWindow << " ID:" << pWindow->mId <<  " x:" << LOWORD(lParam) << " y:" << HIWORD(lParam) << log::end;
        // @todo: moved event
        // lParam: x: (int)(short) LOWORD(lParam)
        //         y: (int)(short) HIWORD(lParam)
        // wParam (no used)
        break; 
      }
      case WM_MOVING: { break; }
      case WM_SIZE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:WM_SIZE::" << pWindow << " ID:" << pWindow->mId <<  " x:" << LOWORD(lParam) << " y:" << HIWORD(lParam) << log::end;
        
        // @todo: sized event
        
        // @todo: window states
        // EState eState   = (wParam == SIZE_MAXSHOW) ? EState::MAXIMIZED : (wParam == SIZE_MINIMIZED ? EState::MINIMIZED : EState::_STATE_);
        // pWindow->mState = (pWindow->mState & ~EState::MAXIMIZED & ~EState::MINIMIZED) | eState;
        
        (pWindow->mLayout) && pWindow->mLayout->layout(pWindow);
        
        // wParam: 4 SIZE_MAXHIDE   to all popup when other window is maximized
        //         3 SIZE_MAXIMIZED the window has been maximized
        //         2 SIZE_MAXSHOW   to all popup when other window has been restored
        //         1 SIZE_MINIMIZED the window has been minimized
        //         0 SIZE_RESOTRED  resized (but not minimized or maximized)
        // LOWORD(lParam): width  (client area)
        // HIWORD(lParam): height (client area)
        break; 
      }
      case WM_SIZING: { break; }
      case WM_MOUSEACTIVATE: { break; }
      case WM_MOUSEHOVER: { break; }
      case WM_MOUSELEAVE: { break; }
      case WM_LBUTTONDOWN: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        log::nfo << "   W:WM_LBUTTONDOWN::" << pWindow << " ID:" << pWindow->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam) << log::end;
        
        // @todo: mousedown event
        // @todo: click event
        
        // wParam: 0x0002 MK_RBUTTON  (virtual keys)
        //         0x0004 MK_SHIFT
        //         0x0008 MK_CONTROL
        //         0x0010 MK_MBUTTON
        //         0x0020 MK_XBUTTON1
        //         0x0040 MK_XBUTTON2
        // LOWORD(lParam): x mouse position (reltive to the upper left conner of the client area)
        // HIWORD(lParam): y mouse position
        break;
      }
      case WM_LBUTTONUP: { break; }
      case WM_LBUTTONDBLCLK: { break; }
      case WM_RBUTTONUP: { break; }
      case WM_KEYDOWN: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        log::nfo << "   W:WM_KEYDOWN::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << (char)(wParam) << " lParam:" << lParam << log::end;
    
        switch (wParam) {
          case 'Q'      : ::PostQuitMessage(0); break;
          case VK_ESCAPE: ::PostQuitMessage(0); break;
        }
        
        // HWND hFocused = ::GetFocus();        // get handle to current keyboard focused window
        // HWND hActive  = ::GetActiveWindow(); // get handle to current active window
    
        // auto pEvent     = new CKeyEvent(EEvent::KEYDOWN, pWindow);
        // pEvent->mKey    = static_cast<char>(wParam);
    
        // bool bTriggered = pWindow->handle(pEvent);
    
        // while (pEvent->doPropagation() && pWindow->hasParent()) {
        //  pWindow    = pWindow->getParent();
        //  bTriggered = pWindow->handle(pEvent) && bTriggered;
        //}
    
        // if (bTriggered) {_DELETE_(pEvent); return 0;}
    
        // wParam: virtual key code 
        // lParam: 00-15 bits: repeat count of the current key (user holds key pressed)
        //         16-23 bits: scan code (OEM)
        //            24 bit : extended key? (right ALT, CTRL) (for 101,102 key keyboard)
        //         25-28 bits: reserved (DO NOT USE)
        //            29 bit : context code (0 for WM_KEYDOWN)
        //            30 bit : prev key state (1 down, 0 up) (1 if down was already pressed)
        //            31 bit : transition state (0 for WM_KEYDOWN)
        // MSG sMsg; ::TranslateMessage(&sMsg);
        break;
      }
      case WM_KEYUP: {
        break;
        // wParam: virtual key code 
        // lParam: 00-15 bits: repeat count (1 for WM_KEYUP)
        //         16-23 bits: scan code (OEM)
        //            24 bit : extended key? (right ALT, CTRL) (for 101,102 key keyboard)
        //         25-28 bits: reserved (DO NOT USE)
        //            29 bit : context code (0 for WM_KEYUP)
        //            30 bit : prev key state (1 for WM_KEYUP)
        //            31 bit : transition state (1 for WM_KEYUP)
        // return 0; if message was processed
      }
      case WM_ERASEBKGND: { break; }
      case WM_NCPAINT: { break; }
      case WM_PAINT: { break; }
      default: break;
    }
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam); // "For all message I did not handle above, do nothing!"
  }  
}}
