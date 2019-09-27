#include "cym/uix/CBrush.hpp"
#include "cym/uix/CBitmap.hpp"

namespace cym { namespace uix {
  CBrush::CBrush() {
    log::nfo << "uix::CBrush::CBrush()::" << this << " TYPE:" << int(mType) << log::end;
  }
  
  CBrush::CBrush(SColor&& sColor) : mType{EBrush::SOLID}, mColor{std::move(sColor)} {
    log::nfo << "uix::CBrush::CBrush(SColor&&)::" << this << " TYPE:" << int(mType) << log::end;
  }
  
  CBrush::CBrush(SColor&& sColor, int&& nHatch) : mType{EBrush::HATCH}, mColor{std::move(sColor)}, mHatch{std::move(nHatch)} { 
    log::nfo << "uix::CBrush::CBrush(SColor&&,int)::" << this << " TYPE:" << int(mType) << log::end;
  }
  
  CBrush::CBrush(CBitmap*&& pBitmap) : mType{EBrush::PATTERN}, mBitmap{std::move(pBitmap)} { 
    log::nfo << "uix::CBrush::CBrush(CBitmap*&&)::" << this << " TYPE:" << int(mType) << log::end;
  } 
    
  CBrush::~CBrush() {
    log::nfo << "uix::CBrush::~CBrush()::" << this << " TYPE" << int(mType) << log::end;
    DELETE(mBitmap);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CBrush::init() {
    log::nfo << "uix::CBrush::init()::" << this << " TYPE:" << int(mType) << log::end;
    switch (mType) {
      case EBrush::NONE:    { break; }
      case EBrush::SOLID:   { mHandle = ::CreateSolidBrush(COLORREF(mColor));         break; }
      case EBrush::HATCH:   { mHandle = ::CreateHatchBrush(mHatch, COLORREF(mColor)); break; }
      case EBrush::PATTERN: { mHandle = ::CreatePatternBrush(HBITMAP(*mBitmap));      break; }
    }
    return (mHandle != NULL);
  }
}}
