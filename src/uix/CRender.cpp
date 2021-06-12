#include "uix/CRender.hpp"

namespace uix {
  CRender::CRender(CWindow* pWindow, const CContext::SConfig& tConfig /*= {}*/) : mWindow{pWindow}, mConfig{tConfig} {
    CYM_LOG_NFO("uix::CRender::CRender()::" << this);
  }
  
  CRender::~CRender() {
    CYM_LOG_NFO("uix::CRender::~CRender()::" << this);
    DELETE(mContext);
  }
  
  bool CRender::init(uint nHints) {
    mContext = new CContext(mWindow, mConfig);
    return true;
  }
  
  bool        CRender::swap()    const       { return mContext->swap(); }
  bool        CRender::current() const       { return mContext->current(); }
  bool        CRender::clear(int nBit) const { return mContext->clear(nBit); }
  bool        CRender::reset() const         { return mContext->reset(); }
  const char* CRender::version() const       { return mContext->version(); }
  
  void CRender::onResize(CEvent* pEvent) {
    CYM_LOG_NFO("uix::CRender::onResize(CEvent*)::" << this << " " << *pEvent);
    // update render viewport
    GLCALL(::glViewport(pEvent->clientX(),pEvent->clientY(),pEvent->width(),pEvent->height()));
  }
}
