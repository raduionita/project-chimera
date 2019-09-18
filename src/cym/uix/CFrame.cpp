#include "cym/uix/CFrame.hpp"

namespace cym { namespace uix {
  CFrame::CFrame(int nHints/*=ZERO*/) {
    log::nfo << "uix::CFrame::CFrame(int)::" << this << log::end;
    init(nullptr, nHints | CFrame::STYLE);
  }
  
  CFrame::CFrame(CWindow* pParent/*=nullptr*/, int nHints/*=ZERO*/) {
    log::nfo << "uix::CFrame::CFrame(CWindow*,int)::" << this << log::end;
    init(pParent, nHints | CFrame::STYLE);
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
  
    (nHints & EHint::VISIBLE)    && show();
    (nHints & EHint::MAXIMIZE)   && maximize();
    (nHints & EHint::MINIMIZE)   && minimize();
    (nHints & EHint::AUTOWH)     && size(640,480);
    (nHints & EHint::AUTOXY)     && (nHints |= EHint::CENTER);
    (nHints & EHint::CENTER)     && center();
    (nHints & EHint::FULLSCREEN) && fullscreen();
    
    return mInited;
  }
}}
