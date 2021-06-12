#include "uix/CSurface.hpp"
#include "uix/CEvent.hpp"

namespace uix {
  CSurface::CSurface(CWindow* pParent, uint nHints) : mContext{new CContext{this}} {
    CYM_LOG_NFO("uix::CSurface::CSurface(CWindow*,uint)::" << this);
    CSurface::init(pParent,"",AUTO,nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CSurface::CSurface(CWindow* pParent, CContext* pContext, uint nHints) : mContext{pContext} {
    CYM_LOG_NFO("uix::CSurface::CSurface(CWindow*,CContext*,uint)::" << this);
    CSurface::init(pParent,"",AUTO,nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CSurface::CSurface(CWindow* pParent, const CContext::SConfig& sConfig/*={}*/,uint nHints/*=WINDOW*/) : mContext{new CContext{this,sConfig}} {
    CYM_LOG_NFO("uix::CSurface::CSurface(CWindow*,CContext::SConfig&,uint)::" << this);
    CSurface::init(pParent,"",AUTO,nHints|WINDOW|EWindow::VISIBLE);
  }
  
  CSurface::~CSurface() {
    CYM_LOG_NFO("uix::CSurface::~CSurface()::" << this);
    CSurface::free();
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CSurface::init(CWindow* pParent/*=nullptr*/, const CContext::SConfig& tConfig/*={}*/,const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CSurface::init(CWindow*,CContext::SConfig&,CString&,SArea&,uint)::" << this);
    
    RETURN((mState & EState::INITED),true);
    
    bool bInited = CSurface::init(pParent,tTitle,tArea,nHints) && mContext->init(this);
    
    attach(this, uix::CEvent::EType::RESIZE,  &uix::CSurface::onResize);
    
    return bInited;
  }
  
  bool CSurface::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CSurface::init(CWindow*,CString&,SArea&,uint)::" << this);
    
    RETURN((mState & EState::INITED),true);
    
    bool bInited = CPanel::init(pParent,tTitle,tArea,nHints) && mContext->init(this);
    
    attach(this, uix::CEvent::EType::RESIZE,  &uix::CSurface::onResize);
    
    return bInited;
  }
  
  bool        CSurface::current() const       { return mContext->current(); }
  bool        CSurface::clear(int nBit) const { return mContext->clear(nBit); }
  bool        CSurface::reset() const         { return mContext->reset(); }
  const char* CSurface::version() const       { return mContext->version(); }
  
  void CSurface::onResize(CEvent* pEvent) {
    CYM_LOG_NFO("uix::CSurface::onResize(CEvent*)::" << this << " " << *pEvent);
    // update render viewport
    GLCALL(::glViewport(pEvent->clientX(),pEvent->clientY(),pEvent->width(),pEvent->height()));
  }
}
