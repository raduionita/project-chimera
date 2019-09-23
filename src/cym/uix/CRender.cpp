#include "cym/uix/CRender.hpp"

namespace cym { namespace uix {
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
  
  bool CRender::swap()    const       { return mContext->swap(); }
  bool CRender::current() const       { return mContext->current(); }
  bool CRender::clear(int nBit) const { return mContext->clear(nBit); }
  bool CRender::reset() const         { return mContext->reset(); }
}}