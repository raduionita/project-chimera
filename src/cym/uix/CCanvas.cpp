#include "cym/uix/CCanvas.hpp"
#include "cym/uix/CContext.hpp"

namespace cym { namespace uix {
  CCanvas::CCanvas(int nHints) {
    std::cout << "uix::CCanvas::CCanvas(int)::" << this << std::endl;
    init(nullptr, {}, "", SShape::DEFAULT, nHints);
  }
  
  CCanvas::CCanvas(const SShape& sShape, int nHints/*=0*/) {
    std::cout << "uix::CCanvas::CCanvas(SShape&,int)::" << this << std::endl;
    init(nullptr, {}, "", sShape, nHints);
  }
  
  CCanvas::CCanvas(const SString& sTitle, const SShape& sShape, int nHints/*=0*/) {
    std::cout << "uix::CCanvas::CCanvas(SString,SShape&,int)::" << this << std::endl;
    init(nullptr, {}, sTitle, sShape, nHints);
  }
  
  CCanvas::CCanvas(const SOptions& sOptions, const SString& sTitle/*=""*/, const SShape& sShape/*=SShape::DEFAULT*/, int nHints/*=0*/) {
    std::cout << "uix::CCanvas::CCanvas(SOptions&,SString&,SShape&,int)::" << this << std::endl;
    init(nullptr, sOptions, sTitle, sShape, nHints);
  }
  
  CCanvas::CCanvas(CWindow* pParent, const SOptions& sOptions/*={}*/, const SString& sTitle/*=""*/, const SShape& sShape/*=SShape::DEFAULT*/, int nHints/*=0*/) {
    std::cout << "uix::CCanvas::CCanvas(CWindow*,SOptions&,SString&,SShape&,int)::" << this << std::endl;
    init(pParent, sOptions, sTitle, sShape, nHints);
  }
  
  CCanvas::~CCanvas() {
    std::cout << "uix::CCanvas::~CCanvas()::" << this << std::endl;
    DELETE(mContext);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCanvas::init(CWindow* pParent, const SOptions& sOptions, const SString& sTitle, const SShape& sShape, int nHints) {
    std::cout << "uix::CCanvas::init(CWindow*,SOptions&,SString&,SShape&,int)::" << this << std::endl;
  
    mInited = super::init(pParent, sTitle, sShape, nHints);
    
    mInited && (mContext = new CContext(this, sOptions));
    
    return mInited;
  }
}}
