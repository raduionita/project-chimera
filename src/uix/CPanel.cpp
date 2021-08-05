#include "uix/CPanel.hpp"

namespace uix {
  CPanel::CPanel(CWindow* pParent, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CPanel::CPanel(CWindow*,uint)::" << this);
    CPanel::init(pParent,"",AUTO,nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CPanel::CPanel(CWindow* pParent, const SArea& tArea, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CPanel::CPanel(CWindow*,SArea&,uint)::" << this);
    CPanel::init(pParent,"",tArea,nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CPanel::~CPanel() {
    CYM_LOG_NFO("uix::CPanel::~CPanel()::" << this);
    CPanel::free();
  }
  
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CPanel::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CPanel::init(uint)::" << this);
  
    RETURN((mState & EState::INITED),true);
    
    if (!super::init(pParent,tTitle,tArea,nHints)) {
      CYM_LOG_NFO("[CPanel] super::init() failed!");
      ::MessageBox(NULL, "[CPanel] super::init() failed!", "Error", MB_OK);
      return false;
    }
  
    (mHints & EWindow::VISIBLE) && show();
    (mHints & EWindow::AUTOXY)  && move(AUTO, AUTO);
    (mHints & EWindow::AUTOWH)  && size(AUTO, AUTO); // init w/ parent size
    (mHints & EWindow::CENTER)  && center();

    return (mState = (mState | EState::INITED));
  }
}
