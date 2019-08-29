#include "cym/uix/CWindow.hpp"

namespace cym { namespace uix {
  std::map<SString, LPTSTR> CWindow::sRegistry;
  
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

  bool CWindow::init(CWindow* pParent, const SShape& sShape, int nHints) {
    std::cout << "uix::CWindow::init(CWindow*,SShape&,int)::" << this << " CNAME:" << mCname << std::endl;
    
    mParent = pParent;
    
    return true;
  }
  
  bool CWindow::free() {
    std::cout << "uix::CWindow::free()::" << this << std::endl;
    
    // @todo: missing children
    
    
    // release 
    ::ReleaseDC(mHandle, ::GetDC(mHandle));
    // delete handle
    ::DestroyWindow(mHandle);
    // unregister mCname class
    ::UnregisterClass(mCname.c_str(), (HINSTANCE)(*CApplication::getInstance()));
    // return success
    return true;
  }
  
  LPTSTR CWindow::classify() {
    auto it = CWindow::sRegistry.find(mCname);
    if (it != CWindow::sRegistry.end()) { // return
      std::cout << "uix::CWindow::classify()::" << this << "::return CNAME:" << mCname << std::endl;
      return it->second;
    } else {                              // insert
      std::cout << "uix::CWindow::classify()::" << this << "::insert CNAME:" << mCname << std::endl;
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
        mCname.c_str(),                           // LPCTSTR   // lpszClassName
        ::LoadIcon(NULL, IDI_APPLICATION)         // HICON     // hIconSm
      };
      // register
      LPTSTR szWndCls = MAKEINTATOM(::RegisterClassEx(&wndcls));
      // check
      if (szWndCls == NULL) {
        std::cout << "[CWindow] RegisterClassEx failed!" << std::endl;
        ::MessageBox(NULL, "[CWindow] RegisterClassEx failed!", "ERROR", MB_OK);
      } else {
        CWindow::sRegistry.insert(std::make_pair(mCname, szWndCls));
      }
      // return
      return szWndCls;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CLayout* CWindow::layout() const {
    return mLayout;
  }
  
  CWindow* CWindow::parent() const {
    return mParent;
  }
  
  bool CWindow::title(const SString& sTitle) {
    return ::SetWindowText(mHandle, sTitle.c_str());
  }
  
  SString CWindow::title() const {
    CHAR szTitle[256];
    ::GetWindowTextA(mHandle, szTitle, 256);
    return SString(szTitle);
  }
  
  bool CWindow::show(int nHints/*=1*/) {
    // @todo:   0b = hide
    // @todo:   1b = show | make visible
    // @todo:  01b = 2 = maximize
    return true;
  }
  
  bool CWindow::hide(int nHints/*=1*/) {
    // @todo:   0b = show
    // @todo:   1b = hide | make invisible
    // @todo:  01b = 2 = minimize
    return true;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  // CWindow::CRegistry::CRegistry() {
  //   std::cout << "uix::CWindow::CRegistry::CRegistry()::" << this << std::endl;
  // }
  //
  // CWindow::CRegistry::~CRegistry() {
  //   std::cout << "uix::CWindow::CRegistry::~CRegistry()::" << this << std::endl;
  //   // @todo: delete all classes
  // }
  //
  // bool CWindow::CRegistry::insert(WNDCLASSEX* pWndcls) {
  //   return false;
  // }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  LRESULT CWindow::proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // @todo: add more events
    switch (uMsg) {
      case WM_NCCREATE: { break; }
      case WM_CREATE: { break; }
      case WM_NOTIFY: { break; }
      case WM_INITDIALOG: { break; }
      case CM_INIT: { break; }
      case WM_CLOSE: { // called on [x] or window menu [Close] // triggers: WM_DESTROY
        CWindow* pWindow = reinterpret_cast<CWindow*>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
        std::cout << "uix::CWindow::proc(...)::" << pWindow << " ID:" << pWindow->mId <<  " W:WM_CLOSE:" << wParam << ":" << lParam << std::endl;
        ::PostQuitMessage(0);
        break;
      }
      case WM_ACTIVATE: { break; }
      case WM_DESTROY: { break; }
      case WM_SETFOCUS: { break; }
      case WM_KILLFOCUS: { break; }
      case WM_SHOWWINDOW: { break; }
      case WM_DRAWITEM: { break; }
      case WM_COMMAND: { break; }
      case WM_MOVE: { break; }
      case WM_MOVING: { break; }
      case WM_SIZE: { break; }
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
