#include "cym/uix/CFrame.hpp"

namespace cym { namespace uix {
  CFrame::CFrame(int nHints/*=ZERO*/) {
    std::cout << "uix::CFrame::CFrame(int)::" << this << std::endl;
    init(nullptr, nHints | CFrame::STYLE);
  }
  
  CFrame::CFrame(CWindow* pParent/*=nullptr*/, int nHints/*=ZERO*/) {
    std::cout << "uix::CFrame::CFrame(CWindow*,int)::" << this << std::endl;
    init(pParent, nHints | CFrame::STYLE);
  }
  
  CFrame::~CFrame() {
    std::cout << "uix::CFrame::~CFrame()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CFrame::init(CWindow* pParent, int nHints) {
    std::cout << "uix::CFrame::init(CWindow*,int)::" << this << std::endl;
  
    RETURN(mInited,true);
    
    if (!super::init(pParent, nHints)) {
      std::cout << "[CFrame] super::init() failed!" << std::endl;
      ::MessageBox(NULL, "[CFrame] super::init() failed!", "Error", MB_OK);
      return false;
    }
    
    if (!super::handle()) {
      std::cout << "[CFrame] super::handle() failed!" << std::endl;
      ::MessageBox(NULL, "[CFrame] super::handle() failed!", "Error", MB_OK);
      return false;
    } 
    
    // add class pointer to handle's user-data // @see CWindow::proc() 
    ::SetWindowLongPtr(mHandle, GWLP_USERDATA, (LONG_PTR)(this));
  
    mInited = style(nHints);
    
    (nHints & EHint::CENTER)   && center();
    (nHints & EHint::MAXIMIZE) && maximize();
    (nHints & EHint::MINIMIZE) && minimize();
    (nHints & EHint::VISIBLE)  && show();
    
    ::SendMessage(mHandle, CM_INIT, 0, 0);
    
    return mInited;
  }
}}
