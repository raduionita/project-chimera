#include "cym/uix/CStyle.hpp"
#include "cym/uix/CBrush.hpp"
#include "cym/uix/CPen.hpp"
#include "cym/uix/CFont.hpp"
#include "cym/uix/CCursor.hpp"
#include "cym/uix/CIcon.hpp"

namespace cym::uix {
  CStyle::CStyle() {
    log::nfo << "uix::CStyle::CStyle()::" << this << log::end;
  }

  CStyle::~CStyle() {
    log::nfo << "uix::CStyle::~CStyle()::" << this << log::end;
    delete mBackground;
    DELETE(mBorder);
    DELETE(mColor);
    DELETE(mFont);
    DELETE(mCursor);
    DELETE(mIcon);
  }
  
  void CStyle::background(CBrush*&& pBrush) {
    if (mBackground != nullptr && mBackground != pBrush) {
      DELETE(mBackground);
    }
    mBackground = std::move(pBrush);
  }
  
  void CStyle::background(SColor&& sColor) {
    if (mBackground != nullptr) {
      DELETE(mBackground);
    }
    mBackground = new CBrush(std::move(sColor));
  }
  
  CBrush* CStyle::background() {
    return !mBackground ? new CBrush : mBackground;
  }
}
