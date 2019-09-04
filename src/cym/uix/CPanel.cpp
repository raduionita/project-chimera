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
    
    (nHints & EHint::VISIBLE) && show();
    (nHints & EHint::AUTOXY)  && move(AUTO,AUTO);
    (nHints & EHint::AUTOWH)  && size(AUTO,AUTO); // init w/ parent size
    (nHints & EHint::CENTER)  && center();

    return mInited;
  }
}}
