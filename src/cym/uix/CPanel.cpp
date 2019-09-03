#include "cym/uix/CPanel.hpp"

namespace cym { namespace uix {
  CPanel::CPanel(CWindow* pParent, int nHints/*=ZERO*/) {
    std::cout << "uix::CPanel::CPanel(CWindow*,int)::" << this << std::endl;
    init(pParent, nHints | CPanel::STYLE);
  }
  
  CPanel::~CPanel() {
    std::cout << "uix::CPanel::~CPanel()::" << this << std::endl;
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CPanel::init(CWindow* pParent, int nHints) {
    std::cout << "uix::CPanel::init(CWindow*,int)::" << this << std::endl;
  
    RETURN(mInited,true);
    
    if (!super::init(pParent, nHints)) {
      std::cout << "[CPanel] super::init() failed!" << std::endl;
      ::MessageBox(NULL, "[CPanel] super::init() failed!", "Error", MB_OK);
      return false;
    }
    
    if (!super::handle()) {
      std::cout << "[CPanel] super::handle() failed!" << std::endl;
      ::MessageBox(NULL, "[CPanel] super::handle() failed!", "Error", MB_OK);
      return false;
    }
    
    if (!super::style(nHints)) {
      std::cout << "[CPanel] super::style() failed!" << std::endl;
      ::MessageBox(NULL, "[CPanel] super::style() failed!", "Error", MB_OK);
      return false;
    }
    
    (nHints & EHint::CENTER)  && center();
    (nHints & EHint::VISIBLE) && show();
    
    ::SendMessage(mHandle, CM_INIT, 0, 0);

    return mInited;
  }
}}
