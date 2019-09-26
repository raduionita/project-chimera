#include "cym/uix/CStyle.hpp"
#include "cym/uix/CBrush.hpp"
#include "cym/uix/CPen.hpp"
#include "cym/uix/CFont.hpp"
#include "cym/uix/CCursor.hpp"
#include "cym/uix/CIcon.hpp"

namespace cym { namespace uix {
  CStyle::CStyle(int nHints) {
    log::nfo << "uix::CStyle::CStyle(int)::" << this << log::end;
    
    // @todo: IF uix::STYLE
      // background brush = UIX_STYLE_BACKGROUND_COLOR
  
    // @todo: ELSE // !uix::STYLE
      // background brush = NULL
  }
  
  CStyle::~CStyle() {
    log::nfo << "uix::CStyle::~CStyle()::" << this << log::end;
    DELETE(mBackground);
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
  
  CBrush* CStyle::background() {
    return !mBackground ? (mBackground = new CBrush) : mBackground;
  }
}}
