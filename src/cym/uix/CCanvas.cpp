#include "cym/uix/CCanvas.hpp"
#include "cym/uix/CContext.hpp"

namespace cym { namespace uix {
  CCanvas::CCanvas(int nHints/*=ZERO*/) {
    log::nfo << "uix::CCanvas::CCanvas(int)::" << this << log::end;
    init(nullptr, {}, nHints | CCanvas::STYLE);
  }
  
  CCanvas::CCanvas(const SConfig& sConfig, int nHints/*=ZERO*/) {
    log::nfo << "uix::CCanvas::CCanvas(SConfig&,int)::" << this << log::end;
    init(nullptr, sConfig, nHints | CCanvas::STYLE);
  }
  
  CCanvas::CCanvas(CWindow* pParent, const SConfig& sConfig/*={}*/, int nHints/*=EHint::FRAME*/) {
    log::nfo << "uix::CCanvas::CCanvas(CWindow*,SConfig&,int)::" << this << log::end;
    init(pParent, sConfig, nHints | CCanvas::STYLE);
  }
  
  CCanvas::~CCanvas() {
    log::nfo << "uix::CCanvas::~CCanvas()::" << this << log::end;
    DELETE(mContext);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCanvas::init(CWindow* pParent, const SConfig& sConfig, int nHints) {
    log::nfo << "uix::CCanvas::init(CWindow*,SConfig&,int)::" << this << log::end;
  
    mInited = super::init(pParent, nHints);
    
    mInited && (mContext = new CContext(this, sConfig));
    
    return mInited;
  }
  
  bool CCanvas::swap()    const       { return mContext->swap(); }
  bool CCanvas::current() const       { return mContext->current(); }
  bool CCanvas::clear(int nBit) const { return mContext->clear(nBit); }
}}
