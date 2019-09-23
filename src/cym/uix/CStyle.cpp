#include "cym/uix/CStyle.hpp"
#include "cym/uix/CBrush.hpp"

namespace cym { namespace uix {
  CStyle::CStyle() {
    log::nfo << "uix::CStyle::CStyle()::" << this << log::end;
  }
  
  CStyle::~CStyle() {
    log::nfo << "uix::CStyle::~CStyle()::" << this << log::end;
  }
  
  void CStyle::background(CBrush* pBrush) {
    DELETE(mBackground);
    mBackground = pBrush;
  }
  
  CBrush* CStyle::background() {
    return !mBackground ? (mBackground = new CBrush) : mBackground;
  }
}}
