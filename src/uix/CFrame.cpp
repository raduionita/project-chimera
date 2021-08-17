#include "uix/CFrame.hpp"

namespace uix {
  CFrame::CFrame(uint nHints) {
    SYS_LOG_NFO("uix::CFrame::CFrame(int)::" << this);
    CFrame::init(nullptr,"",AUTO,nHints|WINDOW);
  }
  
  CFrame::CFrame(CWindow* pParent/*=nullptr*/, uint nHints/*=WINDOW*/) {
    SYS_LOG_NFO("uix::CFrame::CFrame(CWindow*,int)::" << this);
    CFrame::init(pParent,"",AUTO,nHints|WINDOW);
  }
  
  CFrame::CFrame(CWindow* pParent/*=nullptr*/, const CString& tTitle, uint nHints/*=WINDOW*/) {
    SYS_LOG_NFO("uix::CFrame::CFrame(CWindow*,CString&,int)::" << this);
    CFrame::init(pParent,tTitle,AUTO,nHints|WINDOW);
  }
  
  CFrame::~CFrame() {
    SYS_LOG_NFO("uix::CFrame::~CFrame()::" << this);
    CFrame::free();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CFrame::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    SYS_LOG_NFO("uix::CFrame::init(CWindow*,CString&,SArea&,uint)::" << this);
    
    RETURN((mState & EState::INITED),true);
    
    if (!super::init(pParent,tTitle,tArea,nHints)) {
      SYS_LOG_NFO("[CFrame] super::init() failed!");
      ::MessageBox(NULL, "[CFrame] super::init() failed!", "Error", MB_OK);
      return false;
    }
  
    (mHints & EWindow::VISIBLE)    && show();
    (mHints & EWindow::MAXIMIZE)   && maximize();
    (mHints & EWindow::MINIMIZE)   && minimize();
    (mHints & EWindow::AUTOWH)     && size(640, 480);
    (mHints & EWindow::AUTOXY)     && (mHints |= EWindow::CENTER);
    (mHints & EWindow::CENTER)     && center();
    (mHints & EWindow::FULLSCREEN) && fullscreen();
    
    if (!mParent) {
      // if this is toplevel (noparent) => on close => quit app
      attach(this, CEvent::EType::CLOSE, [](CEvent*) { CApplication::instance()->quit(0); });
    }
    
    return (mState = mState | EState::INITED);
  }
}
