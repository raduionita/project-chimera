#include "cym/uix/CPanel.hpp"

namespace cym { namespace uix {
  CPanel::CPanel(CWindow* pParent, int nHints/*=ZERO*/) {
    log::dbg << "uix::CPanel::CPanel(CWindow*,int)::" << this << log::end;
    init(pParent, nHints | CPanel::STYLE);
  }
  
  CPanel::~CPanel() {
    log::dbg << "uix::CPanel::~CPanel()::" << this << log::end;
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CPanel::init(CWindow* pParent, int nHints) {
    log::dbg << "uix::CPanel::init(CWindow*,int)::" << this << log::end;
  
    RETURN(mInited,true);
    
    if (!super::init(pParent, nHints)) {
      log::dbg << "[CPanel] super::init() failed!" << log::end;
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
