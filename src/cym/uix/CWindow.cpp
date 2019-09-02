#include "cym/uix/CWindow.hpp"

namespace cym { namespace uix {
  std::map<TString, LPTSTR> CWindow::sRegistry;
  
  CWindow::CWindow() {
    std::cout << "uix::CWindow::CWindow()::" << this << std::endl;
  }
  
  CWindow::~CWindow() {
    std::cout << "uix::CWindow::~CWindow()::" << this << std::endl;
    // release
    free();
  }
  
  CWindow::CWindow(const CWindow&) {
    std::cout << "uix::CWindow::CWindow(CWindow&)::" << this << std::endl;
    // @todo: complete this
  }
  
  CWindow& CWindow::operator =(const CWindow& that) {
    if (this != &that) {
      std::cout << "uix::CWindow::operator =(CWindow&)::" << this << std::endl;
      // @todo: complete this
    }
    return *this;
  }
  
  CWindow::operator HWND() {
    std::cout << "uix::CWindow::operator HWND()::" << this << std::endl;
    return mHandle;
  }
  
  CWindow::operator const HWND() const {
    std::cout << "uix::CWindow::operator HWND()::" << this << std::endl;
    return mHandle;
  }
  
  CWindow::operator LPTSTR() {
    std::cout << "uix::CWindow::operator LPCSTR()::" << this << std::endl;
    return classify();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CWindow::init(CWindow* pParent, int nHints) {
    std::cout << "uix::CWindow::init(CWindow*,int)::" << this << " NAME:" << name() << std::endl;
    
    // set parent
    mParent = pParent;
    // add to parent's children list
    if (mParent != nullptr) { mParent->mChildren.push_back(this); }
    
    return true;
  }
  
  bool CWindow::free() {
    std::cout << "uix::CWindow::free()::" << this << std::endl;
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
    ::UnregisterClass(name().c_str(), (HINSTANCE)(*CApplication::getInstance()));
    // clear
    mHandle = NULL;
    mInited = false;
    return !mInited;
  }
  
  LPTSTR CWindow::classify() {
    auto cls = name(); 
    auto it  = CWindow::sRegistry.find(cls);
    if (it != CWindow::sRegistry.end()) { // return
      std::cout << "uix::CWindow::classify()::" << this << "::return NAME:" << cls << std::endl;
      return it->second;
    } else {                              // insert
      std::cout << "uix::CWindow::classify()::" << this << "::insert NAME:" << cls << std::endl;
      WNDCLASSEX wndcls = {
        sizeof(WNDCLASSEX),                       // UINT      // cbSize        // struct size  
        CS_HREDRAW | CS_VREDRAW | CS_OWNDC,       // UINT      // style
        CWindow::proc,                            // WNDPROC   // lpfnWndProc   // uix::CWidget::proc
        0,                                        // int       // cbClsExtra    // no extra bytes after the window class
        0,                                        // int       // cbWndExtra    // extra bytes to allocate after the win instance 
        (HINSTANCE)(*CApplication::getInstance()),// HINSTANCE // hInstance     // to identify the dll that loads this module  
        ::LoadIcon(NULL, IDI_APPLICATION),        // HICON     // hIcon
        ::LoadCursor(NULL, IDC_ARROW),            // HCURSOR   // hCursor
        (HBRUSH)(NULL_BRUSH),                     // HBRUSH    // hbrBackground
        NULL,                                     // LPCTSTR   // lpszMenuName  // no menu
        cls.c_str(),                              // LPCTSTR   // lpszClassName
        ::LoadIcon(NULL, IDI_APPLICATION)         // HICON     // hIconSm
      };
      // register
      LPTSTR szWndCls = MAKEINTATOM(::RegisterClassEx(&wndcls));
      // check
      if (szWndCls == NULL) {
        std::cout << "[CWindow] RegisterClassEx failed!" << std::endl;
        ::MessageBox(NULL, "[CWindow] RegisterClassEx failed!", "ERROR", MB_OK);
      } else {
        CWindow::sRegistry.insert(std::make_pair(cls, szWndCls));
      }
      // return
      return szWndCls;
    }
  }
  
  inline TString CWindow::name() const {
    return sys::concat("uix::CWindow::", mId);
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
  bool CWindow::show(int nHints/*=1*/) {
    std::cout << "uix::CWindow::show()::" << this << std::endl;
    // @todo:   0b = hide
    // @todo:   1b = show | make visible
    // @todo:  01b = 2 = maximize
    return mInited && ::ShowWindow(mHandle, SW_SHOW);
  }
  
  bool CWindow::hide(int nHints/*=1*/) {
    std::cout << "uix::CWindow::hide()::" << this << std::endl;
    // @todo:   0b = show
    // @todo:   1b = hide | make invisible
    // @todo:  01b = 2 = minimize
    return mInited && ::ShowWindow(mHandle, SW_HIDE);
  }
  
  bool CWindow::focus(int nHints) {
    std::cout << "uix::CWindow::focus()::" << this << std::endl;
    ::SetFocus(mHandle); // returns window w/ previous focus
    return true;
  }
  
  bool CWindow::move(int x, int y) {
    std::cout << "uix::CWindow::move("<< x <<","<< y <<")::" << this << std::endl;
  
    RETURN(!mInited, false);
    
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
    
    RECT sRect = {x, y, 0, 0};
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);

    x = sRect.left + 1; // +1 on windows 10
    // y = y;
    
    return !(mState & EState::MAXIMIZED) && (::SetWindowPos(mHandle, NULL, x, y, 0, 0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOSIZE|SWP_NOACTIVATE));
  }
  
  bool CWindow::size(int w, int h) {
    std::cout << "uix::CWindow::size("<< w <<","<< h <<")::" << this << std::endl;
  
    RETURN(!mInited, false);
    
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
    
    RECT  sRect = {0, 0, w, h};
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);
    
    w = sRect.right  - sRect.left;
    h = sRect.bottom - sRect.top;
    
    return !(mState & EState::MAXIMIZED) && (::SetWindowPos(mHandle, NULL, 0, 0, w, h, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE));
  }
  
  bool CWindow::center() {
    std::cout << "uix::CWindow::center()::" << this << std::endl;
    
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
    std::cout << "uix::CWindow::adjust()::" << this << std::endl;
    
    RETURN(!mInited, {});
  
    // need the styles for correct window shape adjustment
    DWORD dwExStyle = (DWORD)::GetWindowLong(mHandle, GWL_EXSTYLE);
    DWORD dwStyle   = (DWORD)::GetWindowLong(mHandle, GWL_STYLE);
  
    RECT sRect;
    ::AdjustWindowRectEx(&sRect, dwStyle, FALSE, dwExStyle);
    
    return {sRect.left, sRect.top, sRect.right, sRect.bottom};
  }
  
  bool CWindow::style(int nHints/*=0*/) {
    DWORD dwExStyle = 0; // WS_EX_APPWINDOW;
    DWORD dwStyle   = 0;
    
    dwStyle |= nHints & EHint::POPUP    ? WS_POPUP & ~WS_CHILD       : 0;
    dwStyle |= nHints & EHint::CHILD    ? WS_CHILD & ~WS_POPUP       : 0;
    dwStyle |= nHints & EHint::MAXBOX   ? WS_MAXIMIZEBOX             : 0;
    dwStyle |= nHints & EHint::MINBOX   ? WS_MINIMIZEBOX             : 0;
    dwStyle |= nHints & EHint::SYSBOX   ? WS_SYSMENU                 : 0;
    dwStyle |= nHints & EHint::FRAME    ? WS_THICKFRAME | WS_SIZEBOX : 0;
    dwStyle |= nHints & EHint::TITLE    ? WS_CAPTION                 : 0;
    dwStyle |= nHints & EHint::BORDER   ? WS_BORDER                  : 0; 
    dwStyle |= nHints & EHint::VISIBLE  ? WS_VISIBLE                 : 0;
    dwStyle |= nHints & EHint::DISABLE  ? WS_DISABLED                : 0;
    dwStyle |= nHints & EHint::HSCROLL  ? WS_HSCROLL                 : 0;
    dwStyle |= nHints & EHint::VSCROLL  ? WS_VSCROLL                 : 0;
    dwStyle |= nHints & EHint::MINIMIZE ? WS_MINIMIZE                : 0;
    dwStyle |= nHints & EHint::MAXIMIZE ? WS_MAXIMIZE                : 0;
    dwStyle |= nHints & EHint::NOCLIP   ? 0                          : WS_CLIPSIBLINGS;
    dwStyle |= nHints & EHint::NOCLIP   ? 0                          : WS_CLIPCHILDREN;
    
    // reset default window styles // requires SetWindowPos + SWP_FRAMECHANGED
    ::SetWindowLong(mHandle, GWL_STYLE,   dwStyle);
    ::SetWindowLong(mHandle, GWL_EXSTYLE, dwExStyle);
    ::SetWindowPos(mHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE);
    
    return true;
  }
  
  bool CWindow::maximize() {
    std::cout << "uix::CWindow::maximize()::" << this << std::endl;
    return /*(mState |= EState::MAXIMIZED) &&*/ ::ShowWindow(mHandle, SW_MAXIMIZE);
  }
  
  bool CWindow::minimize() {
    std::cout << "uix::CWindow::minimize()::" << this << std::endl;
    return /*(mState |= EState::MINIMIZED) &&*/ ::ShowWindow(mHandle, SW_MINIMIZE);
  }
  
  auto CWindow::layout() const -> decltype(mLayout) {
    return mLayout;
  }
  
  bool CWindow::layout(CLayout* pLayout) {
    mLayout = pLayout;
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
  
  bool CWindow::title(const TString& sTitle) {
    return ::SetWindowText(mHandle, sTitle.c_str());
  }
    
  TString CWindow::title() const {
    CHAR szTitle[256];
    ::GetWindowTextA(mHandle, szTitle, 256);
    return TString(szTitle);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CWindow* CWindow::find(const TString& name) {
    std::cout << "uix::CWindow::find(" << name << ")::" << std::endl;
    CWindow* found = nullptr;
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
        std::cout << "   W:WM_CREATE::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << std::endl;
        // @todo: create event
        break; 
      }
      case WM_NOTIFY: { break; }
      case WM_INITDIALOG: { break; }
      case CM_INIT: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        std::cout << "   W:CM_INIT::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << std::endl;
        return 0;
      }
      case WM_CLOSE: { // called on [x] or window menu [Close] // triggers: WM_DESTROY
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        std::cout << "   W:WM_CLOSE::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << std::endl;
        // @todo: close event
        ::PostQuitMessage(0);
        break;
      }
      case WM_ACTIVATE: { break; }
      case WM_DESTROY: { break; }
      case WM_SETFOCUS: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        std::cout << "   W:WM_SETFOCUS::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << std::endl;
        // @todo: focus event
        break; 
      }
      case WM_KILLFOCUS: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        std::cout << "   W:WM_KILLFOCUS::" << pWindow << " ID:" << pWindow->mId <<  " wParam:" << wParam << " lParam:" << lParam << std::endl;
        // @todo: blur event
        break; 
      }
      case WM_SHOWWINDOW: { break; }
      case WM_DRAWITEM: { break; }
      case WM_COMMAND: { break; }
      case WM_MOVE: {
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        BREAK(!pWindow);
        std::cout << "   W:WM_MOVE::" << pWindow << " ID:" << pWindow->mId <<  " x:" << LOWORD(lParam) << " y:" << HIWORD(lParam) << std::endl;
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
        std::cout << "   W:WM_SIZE::" << pWindow << " ID:" << pWindow->mId <<  " x:" << LOWORD(lParam) << " y:" << HIWORD(lParam) << std::endl;
        
        // @todo: sized event
        
        // EState eState   = (wParam == SIZE_MAXSHOW) ? EState::MAXIMIZED : (wParam == SIZE_MINIMIZED ? EState::MINIMIZED : EState::_STATE_);
        // pWindow->mState = (pWindow->mState & ~EState::MAXIMIZED & ~EState::MINIMIZED) | eState;
        
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
      case WM_LBUTTONDOWN: { break; }
      case WM_LBUTTONUP: { break; }
      case WM_LBUTTONDBLCLK: { break; }
      case WM_RBUTTONUP: { break; }
      case WM_KEYDOWN: { break; }
      case WM_KEYUP: { break; }
      case WM_ERASEBKGND: { break; }
      case WM_NCPAINT: { break; }
      case WM_PAINT: { break; }
      default: break;
    }
    return ::DefWindowProc(hWnd, uMsg, wParam, lParam); // "For all message I did not handle above, do nothing!"
  }  
}}
