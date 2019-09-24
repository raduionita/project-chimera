#include "cym/uix/CStyle.hpp"
#include "cym/uix/CBrush.hpp"
#include "cym/uix/CPen.hpp"

namespace cym { namespace uix {
  CStyle::CStyle(int nHints) {
    log::nfo << "uix::CStyle::CStyle(int)::" << this << log::end;
    
    // @todo: if nothing specific, define as a null style...empty (default win32 style) don't draw anything
  }
  
  CStyle::~CStyle() {
    log::nfo << "uix::CStyle::~CStyle()::" << this << log::end;
  }
  
  void CStyle::background(CBrush*&& pBrush) {
    if (mBackground != nullptr && mBackground != pBrush) {
      DELETE(mBackground);
    }
    mBackground = std::move(pBrush);
  }
  
  CBrush* CStyle::background() {
    return !mBackground ? (mBackground = new CBrush) : mBackground;
  }
}}
