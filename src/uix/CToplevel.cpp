#include "uix/CToplevel.hpp"

namespace uix {
  CToplevel::CToplevel(int nHints/*=ZERO*/) {
    log::nfo << "uix::CToplevel::CToplevel(int)::" << this << log::end;
    init(nullptr, nHints | CToplevel::WINDOW);
  }
  
  CToplevel::~CToplevel() {
    log::nfo << "uix::CToplevel::~CToplevel()::" << this << log::end;
  }
  
  bool CToplevel::init(CWindow* pParent, int nHints) {
    log::nfo << "uix::CToplevel::init(CWindow*,int)::" << this << log::end;
    
    RETURN(mInited,true);
    
    if (!super::init(pParent, nHints)) {
      log::nfo << "[CToplevel] super::init() failed!" << log::end;
      ::MessageBox(NULL, "[CToplevel] super::init() failed!", "Error", MB_OK);
      return false;
    }
    
    attach(this, EEvent::CLOSE, [](CEvent*) { CApplication::instance()->quit(0); });
    
    return mInited;
  }
}
