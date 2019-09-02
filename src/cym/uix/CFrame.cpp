#include "cym/uix/CFrame.hpp"

namespace cym { namespace uix {
  CFrame::CFrame(int nHints/*=EHint::FRAME*/) {
    std::cout << "uix::CFrame::CFrame(int)::" << this << std::endl;
    init(nullptr, nHints);
  }
  
  CFrame::CFrame(CWindow* pParent/*=nullptr*/, int nHints/*=EHint::FRAME*/) {
    std::cout << "uix::CFrame::CFrame(CWindow*,int)::" << this << std::endl;
    init(pParent, nHints);
  }
  
  CFrame::~CFrame() {
    std::cout << "uix::CFrame::~CFrame()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CFrame::init(CWindow* pParent, int nHints) {
    std::cout << "uix::CFrame::init(CWindow*,int)::" << this << std::endl;
  
    RETURN(mInited,true);
    
    mInited = super::init(pParent, nHints);
    
    LPTSTR szWndcls = classify();
    
    RETURN(!szWndcls, false);
    
    mHandle = ::CreateWindowEx(
      0,                                         // DWORD // ex. style (0 = default)
      szWndcls,                                  // LPCSTR window class name
      name().c_str(),                            // LPCSTR window title name
      0,                                         // DWORD // style
      CW_USEDEFAULT, CW_USEDEFAULT,              // (x, y) 
      CW_USEDEFAULT, CW_USEDEFAULT,              // (width, height)
      mParent ? (HWND)(*mParent) : NULL,         // HWND parent handle
      NULL,                                      // HMENU menu handle
      (HINSTANCE)(*CApplication::getInstance()), // HINSTANCE application handle
      this                                       // LPVOID additional app data (@see WM_CREATE & CREATESTRUCT)
    );
    
    if (mHandle == NULL) {
      std::cout << "[CFrame] RegisterClassEx failed!" << std::endl;
      ::MessageBox(NULL, "[CFrame] CreateWindowEx failed!", "Error", MB_OK);
      return false;
    } 
    
    // add class pointer to handle's user-data // @see CWindow::proc() 
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
  
    mInited = style(nHints);
    
    (nHints & EHint::CENTER)   && center();
    (nHints & EHint::MAXIMIZE) && maximize();
    (nHints & EHint::MINIMIZE) && minimize();
    (nHints & EHint::VISIBLE)  && show();
    
    // @todo: styles
    // @todo: hints: auto pos + centered + maximize|minimize + visible
  
    ::SendMessage(mHandle, CM_INIT, 0, 0);
    
    return mInited;
  }
}}
