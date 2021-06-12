#include "uix/CLayout.hpp"
#include "uix/CStyle.hpp"

namespace uix {
  CWindow::~CWindow() {
    CYM_LOG_NFO("uix::CWindow::~CWindow()::" << this);
    // @todo: throw exception if not ::free() NOT called
  }
  
  // cast ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CWindow::operator HWND() {
    CYM_LOG_NFO("uix::CWindow::operator HWND()::" << this);
    return mHandle;
  }
  
  CWindow::operator const HWND() const {
    CYM_LOG_NFO("uix::CWindow::operator HWND()::" << this);
    return mHandle;
  }
  
  CWindow::operator HDC() {
    CYM_LOG_NFO("uix::CWindow::operator HDC()::" << this);
    return ::GetDC(mHandle);
  }
  
  CWindow::operator const HDC() const {
    CYM_LOG_NFO("uix::CWindow::operator HDC()::" << this);
    return ::GetDC(mHandle);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CWindow::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*="*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CWindow::init(CWindow*,CString&,SArea&,uint)::" << this << " NAME:" << name());
    
    mHints  = mHints | nHints | (pParent ? EWindow::VISIBLE : 0);
    mHints  = tArea == AUTO ? (mHints | EWindow::AUTOXY | EWindow::AUTOWH) : ((mHints & ~EWindow::AUTOWH) & ~EWindow::AUTOXY);
    mParent = pParent; 
    mParent && mParent->assign(this);
    mTitle  = tTitle;
    mArea   = tArea;
    mLayout = new CLayout;
  
    WNDCLASSEX sWndCls = {
      sizeof(WNDCLASSEX),                // UINT      // cbSize        // struct size  
      CS_HREDRAW|CS_VREDRAW|CS_OWNDC,    // UINT      // style
      CWindow::proc,                     // WNDPROC   // lpfnWndProc   // uix::CWidget::proc
      0,                                 // int       // cbClsExtra    // no extra bytes after the window class
      0,                                 // int       // cbWndExtra    // extra bytes to allocate after the win getSingleton 
      (HINSTANCE)(*mApplication),        // HINSTANCE // hInstance     // to identify the dll that loads this module  
      ::LoadIcon(NULL, IDI_APPLICATION), // HICON     // hIcon
      ::LoadCursor(NULL, IDC_ARROW),     // HCURSOR   // hCursor
      // @todo: replace by style()->background()
      (HBRUSH)(NULL_BRUSH),              // HBRUSH    // hbrBackground
      NULL,                              // LPCTSTR   // lpszMenuName  // no menu
      name().c_str(),                    // LPCTSTR   // lpszClassName
      ::LoadIcon(NULL, IDI_APPLICATION)  // HICON     // hIconSm
    };
  
    if (!::RegisterClassEx(&sWndCls)) {
      CYM_LOG_NFO("[CWindow] ::RegisterClassEx() failed!");
      ::MessageBox(NULL, "[CWindow] ::RegisterClassEx() failed!", "ERROR", MB_OK);
      return false;
    }
  
    DWORD dwExStyle = 0; // WS_EX_APPWINDOW;
    DWORD dwStyle   = 0;
  
    dwStyle |= mHints & EWindow::POPUP    ? WS_POPUP|WS_OVERLAPPED   : 0;
    dwStyle |= mHints & EWindow::CHILD    ? WS_CHILD                 : 0;
    dwStyle |= mHints & EWindow::MAXBOX   ? WS_MAXIMIZEBOX           : 0;
    dwStyle |= mHints & EWindow::MINBOX   ? WS_MINIMIZEBOX           : 0;
    dwStyle |= mHints & EWindow::SYSBOX   ? WS_SYSMENU               : 0;
    dwStyle |= mHints & EWindow::FRAME    ? WS_THICKFRAME|WS_SIZEBOX : 0;
    dwStyle |= mHints & EWindow::TITLE    ? WS_CAPTION               : 0;
    dwStyle |= mHints & EWindow::BORDER   ? WS_BORDER                : 0;
    dwStyle |= mHints & EWindow::VISIBLE  ? WS_VISIBLE               : 0;
    dwStyle |= mHints & EWindow::DISABLED ? WS_DISABLED              : 0;
    dwStyle |= mHints & EWindow::HSCROLL  ? WS_HSCROLL               : 0;
    dwStyle |= mHints & EWindow::VSCROLL  ? WS_VSCROLL               : 0;
    dwStyle |= mHints & EWindow::MINIMIZE ? WS_MINIMIZE              : 0;
    dwStyle |= mHints & EWindow::MAXIMIZE ? WS_MAXIMIZE              : 0;
    dwStyle |= mHints & EWindow::NOCLIP   ? 0                        : WS_CLIPSIBLINGS;
    dwStyle |= mHints & EWindow::NOCLIP   ? 0                        : WS_CLIPCHILDREN;
  
    mHandle = ::CreateWindowEx(
      dwExStyle,                         // DWORD     // dwExStyle    // ex. style (0 = default)
      name().c_str(),                    // LPCSTR    // lpClassName  // window class name
      name().c_str(),                    // LPCSTR    // lpWindowName // window title name
      dwStyle,                           // DWORD     // dwExStyle    // style
      UIX_WINDOW_AREA_X, UIX_WINDOW_AREA_Y, // int       // x, y 
      UIX_WINDOW_AREA_W, UIX_WINDOW_AREA_H, // int       // width, height
      mParent ? (HWND)(*mParent) : NULL, // HWND      // hWndParent   // parent handle
      NULL,                              // HMENU     // hMenu        // menu handle
      (HINSTANCE)(*mApplication),        // HINSTANCE // hInstance    //  application handle
      this                               // LPVOID    // lpParam      // additional app data (@see WM_CREATE & CREATESTRUCT)
    );
  
    if (!mHandle) {
      ::MessageBox(NULL, "[CWindow] ::CreateWindowEx() failed!", "ERROR", MB_OK);
      CYM_LOG_NFO("[CWindow] ::CreateWindowEx() failed!");
      return false;
    }
  
    // add class pointer to handle's user-data // @see CWindow::proc() 
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
  
    // reset default window styles // requires SetWindowPos + SWP_FRAMECHANGED
    ::SetWindowLong(mHandle, GWL_STYLE,   dwStyle);
    ::SetWindowLong(mHandle, GWL_EXSTYLE, dwExStyle);
    // ::SetWindowPos(mHandle, NULL, 0,0,0,0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
    // add to the message queue // method should exit before this is triggered 
    ::PostMessage(mHandle, CM_INIT, 0, 0);
    
    // @todo: Make this window 70% alpha
    // SetWindowLong(mHandle, GWL_EXSTYLE, GetWindowLong(mHandle, GWL_EXSTYLE) | WS_EX_LAYERED);
    // SetLayeredWindowAttributes(hwnd, 0, (255 * 70) / 100, LWA_ALPHA);
    
    // done initing
    return (mState = (mState | EState::INITED));
  }
  
  bool CWindow::free() {
    CYM_LOG_NFO("uix::CWindow::free()::" << this);
    // remove inited sate
    mState = (mState & ~EState::INITED) | EState::FREED;
    // fire free event
    ::SendMessage(mHandle, CM_FREE, 0, 0);
    // delete children
    for (CWindow* pChild : mChildren) {
      DELETE(pChild);
    }
    // remove from parent
    if (mParent != nullptr) {
      mParent->remove(this);
    }
    // remove proc
    ::SetWindowLongPtr(mHandle, GWLP_WNDPROC, (LONG_PTR)(&::DefWindowProc));
    // release 
    ::ReleaseDC(mHandle, ::GetDC(mHandle));
    // delete handle
    ::DestroyWindow(mHandle);
    // unregister name class
    ::UnregisterClass(name().c_str(), (HINSTANCE)(*CApplication::instance()));
    // clear
    mHandle = NULL;
    delete mLayout;
    return mState & EState::FREED;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CWindow::onInit() { }
  
  void CWindow::onFree() { }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  bool CWindow::show(uint nHints/*=0*/) {
    CYM_LOG_NFO("uix::CWindow::show(uint)::" << this);
    // @todo:   0b = hide
    // @todo:  01b = show | make visible
    // @todo:  10b = 2 = maximize
    return (mState & EState::INITED) && ::ShowWindow(mHandle, SW_SHOW); 
  }
  
  bool CWindow::hide(uint /*nHints=1*/) {
    CYM_LOG_NFO("uix::CWindow::hide(uint)::" << this);
    // @todo:   0b = show
    // @todo:   1b = hide | make invisible
    // @todo:  01b = 2 = minimize
    return (mState & EState::INITED) && ::ShowWindow(mHandle, SW_HIDE);
  }
  
  bool CWindow::focus(uint /*nHints=1*/) {
    CYM_LOG_NFO("uix::CWindow::focus(uint)::" << this);
    ::SetFocus(mHandle); // returns window w/ previous focus
    return true;
  }
  
  bool CWindow::move(int x, int y) {
    CYM_LOG_NFO("uix::CWindow::move("<< x <<","<< y <<")::" << this);
  
    RETURN(!(mState & EState::INITED), false);
    
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
    
    x = x == AUTO ? 0 : x;
    y = y == AUTO ? 0 : y;
    
    RECT sRect = {x, y, 0, 0};
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);

    x = sRect.left; // @todo: +1 issue 'cause of border 
    // y = y;
    
    return !(mState & EState::MAXIMIZED) && !(mState & EState::FULLSCREEN)
        && (::SetWindowPos(mHandle, NULL, x, y, 0, 0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE));
  }
  
  SMove CWindow::move() const {
    RECT sRect {0};
    ::GetClientRect(mHandle, &sRect);
    ::MapWindowPoints(mHandle,::GetParent(mHandle),(LPPOINT)(&sRect),2);
    return {sRect.left,sRect.top};
  }
  
  bool CWindow::size(int w, int h) {
    CYM_LOG_NFO("uix::CWindow::size("<< w <<","<< h <<")::" << this);
  
    RETURN(!(mState & EState::INITED), false);
    
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
    
    w = sWRect.right  - sWRect.left;
    h = sWRect.bottom - sWRect.top;
    
    return !(mState & EState::MAXIMIZED) && !(mState & EState::FULLSCREEN)
        && (::SetWindowPos(hWindow, NULL, 0, 0, w, h, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE));
  }
  
  SSize CWindow::size() const {
    RECT sRect {0};
    ::GetClientRect(mHandle, &sRect);
    ::MapWindowPoints(mHandle,::GetParent(mHandle),(LPPOINT)(&sRect),2);
    return {sRect.right-sRect.left,sRect.bottom-sRect.top};
  }
  
  bool CWindow::area(const SArea& sArea) {
    return move(sArea.x,sArea.y) && size(sArea.w, sArea.h);
  }
  
  SArea CWindow::area() const {
    RECT sRect {0};
    ::GetClientRect(mHandle, &sRect);
    ::MapWindowPoints(mHandle,::GetParent(mHandle),(LPPOINT)(&sRect),2);
    return {sRect.left,sRect.top,sRect.right-sRect.left,sRect.bottom-sRect.top};
  }
  
  bool CWindow::center() {
    CYM_LOG_NFO("uix::CWindow::center()::" << this);
    
    RETURN(!(mState & EState::INITED), false);
    
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
    CYM_LOG_NFO("uix::CWindow::adjust()::" << this);
    
    RETURN(!(mState & EState::INITED), {});
  
    // need the styles for correct window shape adjustment
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
  
    RECT sRect;
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);
    
    return {sRect.left, sRect.top, sRect.right, sRect.bottom};
  }

  bool CWindow::maximize() {
    CYM_LOG_NFO("uix::CWindow::maximize()::" << this);
    return /*(mState |= EState::MAXIMIZED) &&*/ ::ShowWindow(mHandle, SW_MAXIMIZE);
  }
  
  bool CWindow::minimize() {
    CYM_LOG_NFO("uix::CWindow::minimize()::" << this);
    return /*(mState |= EState::MINIMIZED) &&*/ ::ShowWindow(mHandle, SW_MINIMIZE);
  }
  
  bool CWindow::fullscreen(int) {
    CYM_LOG_NFO("uix::CWindow::fullscreen()::" << this);
    return false;
  }
  
  bool CWindow::close() {
    CYM_LOG_NFO("uix::CWindow::close()::" << this);
    return TRUE == ::PostMessage(mHandle, WM_CLOSE, 0, 0);
  }
  
  STATE CWindow::state() const {
    return ::GetWindowState(mHandle);
  }
  
  CLayout* CWindow::layout() const {
    return mLayout;
  }
  
  CLayout* CWindow::layout(CLayout* pLayout) { 
    if (mLayout != pLayout) { 
      delete mLayout; 
      mLayout = pLayout; 
    }
    mLayout->apply(this);
    return pLayout; 
  };
  
  bool CWindow::assign(CWindow* pChild) {
    mChildren.push_back(pChild);
    return true;
  }
  
  bool CWindow::remove(CWindow* pChild) {
    mChildren.erase(std::remove(mChildren.begin(), mChildren.end(), pChild), mChildren.end());
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
    // 1 beause if parent has only 1 attach then I am it
    if (mParent != nullptr && mParent->mChildren.size() > 1) {
      aSiblings.reserve(mParent->mChildren.size()-1);
      decltype(mParent->mChildren)::size_type nPos = 0;
      // for each parent's attach
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
    
  bool CWindow::style(CStyle* pStyle) {
    if (mStyle != nullptr && mStyle != pStyle && mStyle != mApplication->style()) {
      DELETE(mStyle); 
    } 
    mStyle = pStyle;
    return true;
  }
  
  CStyle* CWindow::style() {
    return !mStyle ? mApplication->style() : mStyle;
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CWindow* CWindow::find(const CString& name) {
    return reinterpret_cast<CWindow*>(::GetWindowLongPtr(::FindWindow(NULL, name.c_str()), GWLP_USERDATA));
  }
  
  CWindow* CWindow::find(HWND hWnd) {
    return reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
  }
  
  LRESULT CWindow::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    log::dbg << "uix::CWindow::proc(HWND,UINT,WPARAM,LPARAM)" << log::end;
    switch (uMsg) {
      case WM_NCCREATE: { break; }
      case WM_CREATE: {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        CWindow*      pWindow = reinterpret_cast<CWindow*>(pCreate->lpCreateParams);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_CREATE::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam);
        // @todo: create event
        break; 
      }
      case WM_NOTIFY: { break; }
      case WM_INITDIALOG: { break; }
      case CM_INIT: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::CM_INIT::" << pWindow << " ID:" << pWindow->mId);
        pWindow->onInit();
        return 0;
      }
      case CM_FREE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::CM_FREE::" << pWindow << " ID:" << pWindow->mId);
        pWindow->onFree();
        return 0;
      }
      case CM_FULLSCREEN: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::CM_FULLSCREEN::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam);
        
        pWindow->mState = pWindow->mState | EState::FULLSCREEN;
        
        return 0;
      }
      case CM_WINDOWED: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::CM_WINDOWED::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam);
        
        pWindow->mState = pWindow->mState & ~EState::FULLSCREEN;
        
        return 0;
      }
      case WM_ACTIVATE: { break; }
      case WM_CLOSE: { // called on [x] or window menu [Close] // triggers: WM_DESTROY
        log::nfo << "  W::WM_CLOSE";
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (pWindow) {
          log::nfo << "::" << pWindow << " ID:" << pWindow->mId;
        }
        CYM_LOG_NFO( " wParam:" << wParam << " lParam:" << lParam);
        
        auto pEvent      = new CEvent(CEvent::EType::CLOSE, pWindow);
        bool bHandled    = pWindow->handle(pEvent);
        DELETE(pEvent);
        
        break;
      }
    //case WM_QUIT: // never reached (handled in loop) 
      case WM_DESTROY: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        CYM_LOG_NFO("  W::WM_DESTROY::" << pWindow << " ID:" << (pWindow?pWindow->mId:0));
        break; 
      }
      case WM_SETFOCUS: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_SETFOCUS::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam);
        // @todo: focus event
        break; 
      }
      case WM_KILLFOCUS: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_KILLFOCUS::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam);
        // @todo: blur event
        break; 
      }
      case WM_SHOWWINDOW: { break; }
      case WM_DRAWITEM: { break; }
      case WM_COMMAND: {
        CWindow*  pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        CControl* pButton = reinterpret_cast<CControl*>(::GetWindowLongPtr((HWND)lParam, GWLP_USERDATA));
        BREAK(!pWindow);BREAK(!pButton);
        CYM_LOG_NFO("  W::WM_COMMAND::" << pWindow << "|" << pButton << " ID:" << pWindow->mId << " " << HIWORD(wParam) << ":" << LOWORD(wParam) << " " << lParam);
        
        auto pEvent = new CEvent(CEvent::EType::COMMAND, pWindow);
        pEvent->mControl = pButton; // should be cated to CControl
        
        switch (HIWORD(wParam)) {
          default: pEvent->mState = EState::EMPTY;
          case BN_CLICKED  : pEvent->mState = EState::CLICKED;
          case BN_DBLCLK   : pEvent->mState = EState::DBLCLICKED;
          case BN_DISABLE  : pEvent->mState = EState::DISABLE;
          case BN_PUSHED   : pEvent->mState = EState::PUSHED;
          case BN_UNPUSHED : pEvent->mState = EState::RELEASED;
          case BN_PAINT    : pEvent->mState = EState::PAINTING;
          case BN_SETFOCUS : pEvent->mState = EState::FOCUSED;
          case BN_KILLFOCUS: pEvent->mState = EState::BLURRED;
        }
        
        bool bHandled = pWindow->handle(pEvent);
        
        DELETE(pEvent);
        
        RETURN(bHandled,0);
        
        break; 
        // HIWORD(wParam) : 0 BN_CLICKED                  // clicked
        //                  5 BN_DBLCLK BN_DOUBLECLICKED  // double clck
        //                  4 BN_DISABLE                  // is disabled
        //                  1 BN_PUSHED BN_HILITE         // pushed  | button down!?
        //                  2 BN_UNPUSHED BN_UNHILITE     // release | button up!?
        //                  1 BN_PAINT                    // button should be painter
        //                  6 BN_SETFOCUS                 // keyboard focus
        //                  7 BN_KILLFOCUS                // left keyboard focus
        // LOWORD(wParam) : button id
        // lParam : button hwnd
      }
      case WM_MOVE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_MOVE::" << pWindow << " ID:" << pWindow->mId <<  " x:" << LOWORD(lParam) << " y:" << HIWORD(lParam));
        
        auto pEvent = new CEvent(CEvent::EType::MOVE, pWindow);
        pEvent->mClientX = LOWORD(lParam);
        pEvent->mClientY = HIWORD(lParam);
        
        EState eState   = (wParam == SIZE_MAXSHOW) ? EState::MAXIMIZED : (wParam == SIZE_MINIMIZED ? EState::MINIMIZED : EState::EMPTY);
        pWindow->mState = (pWindow->mState & ~EState::MAXIMIZED & ~EState::MINIMIZED) | eState;
        
        pEvent->mState  = eState;
        
        bool bHandled   = pWindow->handle(pEvent);
        
        DELETE(pEvent);
        
        RETURN(bHandled,0);
        
        // lParam: x: (int)(short) LOWORD(lParam)
        //         y: (int)(short) HIWORD(lParam)
        // wParam (no used)
        break; 
      }
      case WM_MOVING: { break; }
      case WM_SIZE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK((!pWindow));
        // BREAK((!pWindow) || !(pWindow->mState & EState::INITED));
        CYM_LOG_NFO("  W::WM_SIZE::" << pWindow << " ID:" << pWindow->mId <<  " w:" << LOWORD(lParam) << " h:" << HIWORD(lParam));
        
        auto pEvent = new CEvent(CEvent::EType::RESIZE, pWindow);
        pEvent->mWidth  = LOWORD(lParam);
        pEvent->mHeight = HIWORD(lParam);
        
        EState eState   = (wParam == SIZE_MAXSHOW) ? EState::MAXIMIZED : (wParam == SIZE_MINIMIZED ? EState::MINIMIZED : EState::EMPTY);
        pWindow->mState = (pWindow->mState & ~EState::MAXIMIZED & ~EState::MINIMIZED) | eState;
        
        pEvent->mState  = eState;
        
        bool bHandled   = pWindow->handle(pEvent);
        
        DELETE(pEvent);
        
        pWindow->mLayout->apply(pWindow);
        
        RETURN(bHandled,0);
        
        // wParam: 4 SIZE_MAXHIDE   to all popup when other window is maximized
        //         3 SIZE_MAXIMIZED the window has been maximized
        //         2 SIZE_MAXSHOW   to all popup when other window has been restored
        //         1 SIZE_MINIMIZED the window has been minimized
        //         0 SIZE_RESTORED  resized (but not minimized or maximized)
        // LOWORD(lParam): width  (client area)
        // HIWORD(lParam): height (client area)
        break; 
      }
      case WM_SIZING: { break; }
#if UIX_EVENT_MOUSEMOVE == UIX_ON
      case WM_MOUSEMOVE: { 
        CWindow* pWindow = find(hWnd);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_MOUSEMOVE::" << pWindow << " ID:" << pWindow->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam));
        
        // mousedown event
        auto pEvent       = new CEvent(CEvent::EType::MOUSEMOVE, pWindow);
        pEvent->mClientX  = GET_X_LPARAM(lParam);
        pEvent->mClientY  = GET_Y_LPARAM(lParam);
        pEvent->mModifier = wParam & MK_SHIFT ? EMouse::SHIFT : wParam & MK_CONTROL ? EMouse::CONTROL : EMouse::EMPTY;
        pEvent->mButton   = wParam & MK_LBUTTON ? EMouse::LBUTTON : wParam & MK_RBUTTON ? EMouse::RBUTTON : wParam & MK_MBUTTON ? EMouse::MBUTTON : EMouse::EMPTY;
        
#if UIX_EVENT_APPLICATION == UIX_ON
        bool bHandled = CApplication::instance()->handle(pEvent);
#else
        bool bHandled    = pWindow->handle(pEvent);
#if UIX_EVENT_PROPAGATE == UIX_ON
        while (pEvent->propagate() && (pWindow = pWindow->parent())) {
          bHandled = pWindow->handle(pEvent) && bHandled;
        }
        bHandled = pEvent->propagate() ? CApplication::instance()->handle(pEvent) || bHandled : bHandled;
#endif // UIX_EVENT_PROPAGATE
#endif // UIX_EVENT_APPLICATION
        
        DELETE(pEvent);
        
        RETURN(bHandled,0);
        
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
        break; 
      }
#endif//UIX_EVENT_MOUSEMOVE
      case WM_MOUSEACTIVATE: { break; }
      case WM_MOUSEHOVER: { break; }
      case WM_MOUSELEAVE: { break; }
      case WM_LBUTTONDOWN: {
        CWindow* pWindow = find(hWnd);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_LBUTTONDOWN::" << pWindow << " ID:" << pWindow->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam));
        
        // mousedown event
        auto pEvent       = new CEvent(CEvent::EType::LBUTTONDOWN, pWindow);
        pEvent->mClientX  = GET_X_LPARAM(lParam);
        pEvent->mClientY  = GET_Y_LPARAM(lParam);
        pEvent->mModifier = wParam & MK_SHIFT ? EMouse::SHIFT : wParam & MK_CONTROL ? EMouse::CONTROL : EMouse::EMPTY;
        pEvent->mButton   = EMouse::LBUTTON;
        
#if UIX_EVENT_APPLICATION == UIX_ON
        bool bHandled = CApplication::instance()->handle(pEvent);
#else
        bool bHandled    = pWindow->handle(pEvent);
#if UIX_EVENT_PROPAGATE == UIX_ON
        while (pEvent->propagate() && (pWindow = pWindow->parent())) {
          bHandled = pWindow->handle(pEvent) && bHandled;
        }
        bHandled = pEvent->propagate() ? CApplication::instance()->handle(pEvent) || bHandled : bHandled;
#endif // UIX_EVENT_PROPAGATE
#endif // UIX_EVENT_APPLICATION

        DELETE(pEvent);
        
        RETURN(bHandled,0);
        
        break;
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
      }
      case WM_LBUTTONUP: { 
        CWindow* pWindow = find(hWnd);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_LBUTTONUP::" << pWindow << " ID:" << pWindow->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam));
        
        // @todo: click event
        break; 
        // wParam: 0x0002 MK_RBUTTON  (virtual keys)
        //         0x0004 MK_SHIFT
        //         0x0008 MK_CONTROL
        //         0x0010 MK_MBUTTON
        //         0x0020 MK_XBUTTON1
        //         0x0040 MK_XBUTTON2
        // problematic w/ multiple monitors
        // GET_X_LPARAM(lParam): x mouse position (reltive to the upper left conner of the client area)
        // GET_Y_LPARAM(lParam): y mouse position
      }
      case WM_LBUTTONDBLCLK: { break; }
      case WM_RBUTTONDOWN: {
        CWindow* pWindow = find(hWnd);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_RBUTTONDOWN::" << pWindow << " ID:" << pWindow->mId <<  " x:" << GET_X_LPARAM(lParam) << " y:" <<GET_Y_LPARAM(lParam));
        
        // mousedown event
        auto pEvent       = new CEvent(CEvent::EType::RBUTTONDOWN, pWindow);
        pEvent->mClientX  = GET_X_LPARAM(lParam);
        pEvent->mClientY  = GET_Y_LPARAM(lParam);
        pEvent->mModifier = wParam & MK_SHIFT ? EMouse::SHIFT : wParam & MK_CONTROL ? EMouse::CONTROL : EMouse::EMPTY;
        pEvent->mButton   = EMouse::RBUTTON;
        
#if UIX_EVENT_APPLICATION == UIX_ON
        bool bHandled = CApplication::instance()->handle(pEvent);
#else
        bool bHandled    = pWindow->handle(pEvent);
#if UIX_EVENT_PROPAGATE == UIX_ON
        while (pEvent->propagate() && (pWindow = pWindow->parent())) {
          bHandled = pWindow->handle(pEvent) && bHandled;
        }
        bHandled = pEvent->propagate() ? CApplication::instance()->handle(pEvent) || bHandled : bHandled;
#endif // UIX_EVENT_PROPAGATE
#endif // UIX_EVENT_APPLICATION

        DELETE(pEvent);
        
        RETURN(bHandled,0);
        
        break;
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
      }
      case WM_RBUTTONUP: { break; }
      case WM_RBUTTONDBLCLK: { break; }
      case WM_KEYDOWN: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_KEYDOWN::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << (char)(wParam) << " lParam:" << lParam);
        
        // @todo: check if attach or ancestors listen to this event
        
        // HWND hFocused = ::GetFocus();        // get handle to current keyboard focused window
        // HWND hActive  = ::GetActiveWindow(); // get handle to current active window
    
        auto pEvent   = new CEvent(CEvent::EType::KEYDOWN, pWindow);
        pEvent->mKey  = static_cast<char>(wParam);

#if UIX_EVENT_APPLICATION == UIX_ON
        bool bHandled = CApplication::instance()->handle(pEvent);
#else
        bool bHandled = pWindow->handle(pEvent);
#if UIX_EVENT_PROPAGATE == UIX_ON
        while (pEvent->propagate() && (pWindow = pWindow->parent())) {
          bHandled = pWindow->handle(pEvent) && bHandled;
        }
        bHandled = pEvent->propagate() ? CApplication::instance()->handle(pEvent) || bHandled : bHandled;
#endif // UIX_EVENT_PROPAGATE
#endif // UIX_EVENT_APPLICATION
        
        DELETE(pEvent);
    
        RETURN(bHandled,0);
    
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
      case WM_ERASEBKGND: { 
        CWindow* pWindow = find(hWnd);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_ERASEBKGND::" << pWindow << " ID:" << pWindow->mId);
        UNREFERENCED_PARAMETER(lParam);
        break; 
      }
      case WM_NCPAINT: { break; }
      case WM_PAINT: { 
        CWindow* pWindow = find(hWnd);
        BREAK(!pWindow);
        CYM_LOG_NFO("  W::WM_PAINT::" << pWindow << " ID:" << pWindow->mId);
        UNREFERENCED_PARAMETER(lParam);
        UNREFERENCED_PARAMETER(wParam);
        
        // @note: CRender/CCanvas/CSurface should not draw // has not style()

        const bool bStyled = pWindow->style() && !pWindow->style()->background()->null();
        const bool bListen = pWindow->listens(CEvent::EType::PAINT);
  
        if (bStyled || bListen) {
          // state: +paiting
          pWindow->mState = pWindow->mState | EState::PAINTING;
          // start paint
          PAINTSTRUCT sPS;
          HDC         hDC {::BeginPaint(hWnd, &sPS)};
          // draw style
          if (bStyled) {
            HBRUSH hThisBrush = HBRUSH(*(pWindow->style()->background()));
            HBRUSH hPrevBrush = HBRUSH(::SelectObject(hDC, hThisBrush));
            // paint background
            // ::Rectangle(hDC, sPS.rcPaint.left, sPS.rcPaint.top, sPS.rcPaint.right, sPS.rcPaint.bottom);
            ::FillRect(hDC, &sPS.rcPaint, hThisBrush);
            ::SelectObject(hDC, hPrevBrush);
          }
          // handle event
          if (bListen) {
            auto pEvent = new CEvent(CEvent::EType::PAINT, pWindow);
            // handle event
            pWindow->handle(pEvent);
            // no propagation
            DELETE(pEvent);
          }
          // end paint
          ::EndPaint(hWnd, &sPS);
          // state: -paiting
          pWindow->mState = pWindow->mState & ~EState::PAINTING;
          // return 0 = handled
          return 0;
        }
        // ::UpdateWindow(HWND);
        // ::RedrawWindow(HWND, const RECT*, HRGN, UINT); // WM_ERASEBKGND, WM_NCPAINT, WM_PAINT
        // ::InvalidateRect(HWND, const RECT*, WINBOOL);
        break; 
      }
      case CM_CONTEXT: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        
        std::string ctx;
        
        switch (wParam) {
          case CTX_NONE   : ctx.append("NONE"); break;
          case CTX_OPENGL : ctx.append("OPENGL"); break;
          case CTX_VULKAN : ctx.append("VULKAN"); break;
          case CTX_DIRECTX: ctx.append("DIRECTX"); break;
        }
        
        CYM_LOG_NFO("  W::CM_CONTEXT::" << pWindow << " ID:" << pWindow->mId << " " << ctx << " v" << LOWORD(lParam) << "." << HIWORD(lParam));
  
        return 0;
      }
      default: break;
    }
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam); // "For all message I did not handle above, do nothing!"
  }
}
