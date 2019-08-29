#include "cym/uix/CFrame.hpp"

namespace cym { namespace uix {
  CFrame::CFrame(int nHints) : CFrame(nullptr, "", SShape::DEFAULT, nHints) {
    std::cout << "uix::CFrame::CFrame(int)::" << this << std::endl;
    init(nullptr, "", SShape::DEFAULT, nHints);
  }
  
  CFrame::CFrame(CWindow* pParent, const SString& sTitle/*=""*/, const SShape& sShape/*=SShape::DEFAULT*/, int nHints/*=0*/) {
    std::cout << "uix::CFrame::CFrame(CWindow*,SString&,SShape&,int)::" << this << std::endl;
    init(pParent, sTitle, sShape, nHints);
  }
  
  CFrame::~CFrame() {
    std::cout << "uix::CFrame::~CFrame()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CFrame::init(CWindow* pParent, const SString& sTitle, const SShape& sShape, int nHints) {
    std::cout << "uix::CFrame::init(CWindow*,SString&,SShape&,int)::" << this << std::endl;
  
    mInited = init(pParent, sShape, nHints);
    
    (mInited) && (::SetWindowText(mHandle, sTitle.c_str()));
    
    return mInited; 
  }
  
  bool CFrame::init(CWindow* pParent, const SShape& sShape, int nHints) {
    std::cout << "uix::CFrame::init(CWindow*,SShape&,int)::" << this << std::endl;
  
    if (mInited) return mInited;
    
    mInited = super::init(pParent, sShape, nHints);
    
    LPTSTR szWndcls = classify();
    
    RETURN(!szWndcls, false);
    
    DWORD dwExStyle = WS_EX_APPWINDOW;
    DWORD dwStyle   = WS_VISIBLE | WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_BORDER | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
    
    mHandle = ::CreateWindowEx(
      dwExStyle,                                 // DWORD // ex. style (0 = default)
      szWndcls,                                  // LPCSTR window class name
      mCname.c_str(),                            // LPCSTR window title name
      dwStyle,                                   // DWORD // style
      CW_USEDEFAULT, CW_USEDEFAULT,              // (x, y) 
      CW_USEDEFAULT, CW_USEDEFAULT,              // (width, height)
      mParent ? (HWND)(*mParent) : NULL,         // HWND parent handle
      NULL,                                      // HMENU menu handle
      (HINSTANCE)(*CApplication::getInstance()), // HINSTANCE application handle
      this                                       // LPVOID additional app data (@see WM_CREATE)
    );
    
    if (mHandle == NULL) {
      std::cout << "[CFrame] RegisterClassEx failed!" << std::endl;
      ::MessageBox(NULL, "[CFrame] CreateWindowEx failed!", "Error", MB_OK);
      return false;
    } 
    
    // add class pointer to handle's user-data // @see CWindow::proc() 
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
    // reset default window styles
    ::SetWindowLong(mHandle, GWL_STYLE,   dwStyle);
    ::SetWindowLong(mHandle, GWL_EXSTYLE, dwExStyle);
    
    return mInited;
  }
}}
