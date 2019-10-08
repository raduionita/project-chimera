#include "uix/CRender.hpp"

namespace uix {
  CRender::CRender() {
    log::nfo << "uix::CRender::CRender()::" << this << log::end;
  }
  
  CRender::~CRender() {
    log::nfo << "uix::CRender::~CRender()::" << this << log::end;
    DELETE(mContext);
  }
  
  bool CRender::init(CWindow* pWindow, const CContext::SConfig& sConfig) {
    return (mContext = new CContext(pWindow, sConfig));
  }
  
  bool        CRender::swap()    const       { return mContext->swap(); }
  bool        CRender::current() const       { return mContext->current(); }
  bool        CRender::clear(int nBit) const { return mContext->clear(nBit); }
  bool        CRender::reset() const         { return mContext->reset(); }
  const char* CRender::version() const       { return mContext->version(); }
  
  void CRender::onResize(CEvent* pEvent) {
    log::dbg << "uix::CRender::onResize(CEvent*)::" << this << log::end;
    // update render viewport
    ::glViewport(pEvent->clientX(),pEvent->clientY(),pEvent->width(),pEvent->height());
  }
}
