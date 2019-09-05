#include "cym/uix/CCanvas.hpp"
#include "cym/uix/CContext.hpp"

namespace cym { namespace uix {
  CCanvas::CCanvas(int nHints/*=ZERO*/) {
    std::cout << "uix::CCanvas::CCanvas(int)::" << this << std::endl;
    init(nullptr, {}, nHints | CCanvas::STYLE);
  }
  
  CCanvas::CCanvas(const SConfig& sConfig, int nHints/*=ZERO*/) {
    std::cout << "uix::CCanvas::CCanvas(SConfig&,int)::" << this << std::endl;
    init(nullptr, sConfig, nHints | CCanvas::STYLE);
  }
  
  CCanvas::CCanvas(CWindow* pParent, const SConfig& sConfig/*={}*/, int nHints/*=EHint::FRAME*/) {
    std::cout << "uix::CCanvas::CCanvas(CWindow*,SConfig&,int)::" << this << std::endl;
    init(pParent, sConfig, nHints | CCanvas::STYLE);
  }
  
  CCanvas::~CCanvas() {
    std::cout << "uix::CCanvas::~CCanvas()::" << this << std::endl;
    DELETE(mContext);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCanvas::init(CWindow* pParent, const SConfig& sConfig, int nHints) {
    std::cout << "uix::CCanvas::init(CWindow*,SConfig&,int)::" << this << std::endl;
  
    mInited = super::init(pParent, nHints);
    
    mInited && (mContext = new CContext(this, sConfig));
    
    return mInited;
  }
  
  bool CCanvas::swap()    const       { return mContext->swap(); }
  bool CCanvas::current() const       { return mContext->current(); }
  bool CCanvas::clear(int nBit) const { return mContext->clear(nBit); }
}}
