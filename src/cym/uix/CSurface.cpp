#include "cym/uix/CSurface.hpp"

namespace cym { namespace uix {
  CSurface::CSurface(CWindow* pParent, int nHints) {
    log::nfo << "uix::CSurface::CSurface(CWindow*,SConfig&,int)::" << this << log::end;
    init(pParent, {}, nHints | CSurface::STYLE);
  }
  
  CSurface::CSurface(CWindow* pParent, const SConfig& sConfig/*={}*/,int nHints/*=ZERO*/) {
    log::nfo << "uix::CSurface::CSurface(CWindow*,SConfig&,int)::" << this << log::end;
    init(pParent, sConfig, nHints | CSurface::STYLE);
  }
  
  CSurface::~CSurface() {
    log::nfo << "uix::CSurface::~CSurface()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CSurface::init(CWindow* pParent, const CContext::SConfig& sConfig, int nHints) {
    log::nfo << "uix::CSurface::init(CWindow*,SConfig&,int)::" << this << log::end;
    
    mInited = super::init(pParent, nHints);
    
    mInited && (mContext = new CContext(this, sConfig));
    
    return mInited;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CSurface::swap()    const       { return mContext->swap(); }
  bool CSurface::current() const       { return mContext->current(); }
  bool CSurface::clear(int nBit) const { return mContext->clear(nBit); }
  bool CSurface::reset() const         { return mContext->reset(); }
}}
