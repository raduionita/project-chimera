#include "cym/uix/CFrame.hpp"

namespace cym { namespace uix {
  CFrame::CFrame(int nHints) : CFrame(nullptr, "", SShape::DEFAULT, nHints) {
    std::cout << "uix::CFrame::CFrame(int)::" << this << std::endl;
    init(nullptr, "", SShape::DEFAULT, nHints);
  }
  
  CFrame::CFrame(CWindow* pParent, const TString& sTitle/*=""*/, const SShape& sShape/*=SShape::DEFAULT*/, int nHints/*=0*/) {
    std::cout << "uix::CFrame::CFrame(CWindow*,TString&,SShape&,int)::" << this << std::endl;
    init(pParent, sTitle, sShape, nHints);
  }
  
  CFrame::~CFrame() {
    std::cout << "uix::CFrame::~CFrame()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CFrame::init(CWindow* pParent, const TString& sTitle, const SShape& sShape, int nHints) {
    std::cout << "uix::CFrame::init(CWindow*,TString&,SShape&,int)::" << this << std::endl;
  
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
    
    // @todo: styles
    // @todo: hints: auto pos + centered + maximize|minimize + visible
  
    ::SendMessage(mHandle, CM_INIT, 0, 0);
    
    return mInited;
  }
}}
