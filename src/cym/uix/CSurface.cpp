#include "cym/uix/CSurface.hpp"

namespace cym { namespace uix {
  CSurface::CSurface(CWindow* pParent, int nHints) {
    log::nfo << "uix::CSurface::CSurface(CWindow*,CContext::SConfig&,int)::" << this << log::end;
    init(pParent, {}, nHints | CSurface::WINDOW);
  }
  
  CSurface::CSurface(CWindow* pParent, const CContext::SConfig& sConfig/*={}*/,int nHints/*=ZERO*/) {
    log::nfo << "uix::CSurface::CSurface(CWindow*,CContext::SConfig&,int)::" << this << log::end;
    init(pParent, sConfig, nHints | CSurface::WINDOW);
  }
  
  CSurface::~CSurface() {
    log::nfo << "uix::CSurface::~CSurface()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CSurface::init(CWindow* pParent, const CContext::SConfig& sConfig, int nHints) {
    log::nfo << "uix::CSurface::init(CWindow*,CContext::SConfig&,int)::" << this << log::end;
    return mInited = (CPanel::init(pParent, nHints) && CRender::init(this, sConfig));
  }
}}
