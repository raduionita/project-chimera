#include "uix/CFrame.hpp"

namespace uix {
  CFrame::CFrame(int nHints/*=ZERO*/) {
    log::nfo << "uix::CFrame::CFrame(int)::" << this << log::end;
    init(nullptr, nHints | CFrame::WINDOW);
  }
  
  CFrame::CFrame(CWindow* pParent/*=nullptr*/, int nHints/*=ZERO*/) {
    log::nfo << "uix::CFrame::CFrame(CWindow*,int)::" << this << log::end;
    init(pParent, nHints | CFrame::WINDOW);
  }
  
  CFrame::~CFrame() {
    log::nfo << "uix::CFrame::~CFrame()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CFrame::init(CWindow* pParent, int nHints) {
    log::nfo << "uix::CFrame::init(CWindow*,int)::" << this << log::end;
  
    RETURN(mInited,true);
    
    if (!super::init(pParent, nHints)) {
      log::nfo << "[CFrame] super::init() failed!" << log::end;
      ::MessageBox(NULL, "[CFrame] super::init() failed!", "Error", MB_OK);
      return false;
    }
  
    (nHints & EWindow::VISIBLE)    && show();
    (nHints & EWindow::MAXIMIZE)   && maximize();
    (nHints & EWindow::MINIMIZE)   && minimize();
    (nHints & EWindow::AUTOWH)     && size(640, 480);
    (nHints & EWindow::AUTOXY)     && (nHints |= EWindow::CENTER);
    (nHints & EWindow::CENTER)     && center();
    (nHints & EWindow::FULLSCREEN) && fullscreen();
    
    return mInited;
  }
}
