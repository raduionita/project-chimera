#include "cym/uix/CSurface.hpp"

namespace cym { namespace uix {
  CSurface::CSurface(CWindow* pParent, int nHints) {
    std::cout << "uix::CSurface::CSurface(CWindow*,SConfig&,int)::" << this << std::endl;
    init(pParent, {}, nHints | CSurface::STYLE);
  }
  
  CSurface::CSurface(CWindow* pParent, const SConfig& sConfig/*={}*/,int nHints/*=ZERO*/) {
    std::cout << "uix::CSurface::CSurface(CWindow*,SConfig&,int)::" << this << std::endl;
    init(pParent, sConfig, nHints | CSurface::STYLE);
  }
  
  CSurface::~CSurface() {
    std::cout << "uix::CSurface::~CSurface()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CSurface::init(CWindow* pParent, const CContext::SConfig& sConfig, int nHints) {
    std::cout << "uix::CSurface::init(CWindow*,SConfig&,int)::" << this << std::endl;
    
    mInited = super::init(pParent, nHints);
    
    mInited && (mContext = new CContext(this, sConfig));
    
    return mInited;
  }
    
  bool CSurface::swap()    const { return mContext->swap(); }
  bool CSurface::current() const { return mContext->current(); }
}}
