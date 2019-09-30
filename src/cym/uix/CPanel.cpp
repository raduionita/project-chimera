#include "cym/uix/CPanel.hpp"

namespace cym::uix {
  CPanel::CPanel(CWindow* pParent, int nHints/*=ZERO*/) {
    log::nfo << "uix::CPanel::CPanel(CWindow*,int)::" << this << log::end;
    init(pParent, nHints | CPanel::WINDOW);
  }
  
  CPanel::~CPanel() {
    log::nfo << "uix::CPanel::~CPanel()::" << this << log::end;
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CPanel::init(CWindow* pParent, int nHints) {
    log::nfo << "uix::CPanel::init(CWindow*,int)::" << this << log::end;
  
    RETURN(mInited,true);
    
    if (!super::init(pParent, nHints)) {
      log::nfo << "[CPanel] super::init() failed!" << log::end;
      ::MessageBox(NULL, "[CPanel] super::init() failed!", "Error", MB_OK);
      return false;
    }
  
    (nHints & EWindow::VISIBLE) && show();
    (nHints & EWindow::AUTOXY) && move(AUTO, AUTO);
    (nHints & EWindow::AUTOWH) && size(AUTO, AUTO); // init w/ parent size
    (nHints & EWindow::CENTER) && center();

    return mInited;
  }
}
