#include "cym/uix/CSurface.hpp"

namespace cym { namespace uix {
  CSurface::CSurface(int nHints/*=ZERO*/) {
    std::cout << "uix::CSurface::CSurface(int)::" << this << std::endl;
    init(nullptr, {}, nHints | CSurface::STYLE);
  }
  
  CSurface::~CSurface() {
    std::cout << "uix::CSurface::~CSurface()::" << this << std::endl;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CSurface::init(CWindow* pWindow, const CContext::SConfig& sConfig, int nHints) {
    std::cout << "uix::CSurface::init(CWindow*,SConfig&,int)::" << this << std::endl;
    
    return mInited;
  }
}}
