#include "cym/uix/CBrush.hpp"
#include "cym/uix/CBitmap.hpp"

namespace cym { namespace uix {
  CBrush::CBrush() {
    log::nfo << "uix::CBrush::CBrush()::" << this << log::end;
    mHandle = HBRUSH(NULL_BRUSH);
  }
    
  CBrush::~CBrush() {
    log::nfo << "uix::CBrush::~CBrush()::" << this << log::end;
    DELETE(mBitmap);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CBrush::init() {
    log::nfo << "uix::CBrush::init()" << log::end;
    switch(mType) { 
      case EBrush::SOLID:   { mHandle = ::CreateSolidBrush(mColor);         break; }
      case EBrush::HATCH:   { mHandle = ::CreateHatchBrush(mHatch, mColor); break; }
      case EBrush::PATTERN: { mHandle = ::CreatePatternBrush(HBITMAP(*mBitmap));     break; }
    }
    return (mHandle != NULL);
  }
}}
