#include "uix/CBrush.hpp"
#include "uix/CBitmap.hpp"

namespace uix {
  CBrush::CBrush() {
    CYM_LOG_NFO("uix::CBrush::CBrush()::" << this << " TYPE:" << int(mType));
    mInited = true; // for quick exiting
  }
  
  CBrush::CBrush(SColor&& sColor) : mType{EBrush::SOLID}, mColor{std::move(sColor)} {
    CYM_LOG_NFO("uix::CBrush::CBrush(SColor&&)::" << this << " TYPE:" << int(mType));
  }
  
  CBrush::CBrush(SColor&& sColor, int&& nHatch) : mType{EBrush::HATCH}, mColor{std::move(sColor)}, mHatch{std::move(nHatch)} { 
    CYM_LOG_NFO("uix::CBrush::CBrush(SColor&&,int)::" << this << " TYPE:" << int(mType));
  }
  
  CBrush::CBrush(CBitmap*&& pBitmap) : mType{EBrush::PATTERN}, mBitmap{std::move(pBitmap)} { 
    CYM_LOG_NFO("uix::CBrush::CBrush(CBitmap*&&)::" << this << " TYPE:" << int(mType));
  } 
    
  CBrush::~CBrush() {
    CYM_LOG_NFO("uix::CBrush::~CBrush()::" << this << " TYPE:" << int(mType));
    DELETE(mBitmap);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CBrush::init() {
    CYM_LOG_NFO("uix::CBrush::init()::" << this << " TYPE:" << int(mType));
    if (mInited) return true; // quick exit
    switch (mType) {
      case EBrush::NONE:    { break; }
      case EBrush::SOLID:   { mHandle = ::CreateSolidBrush(COLORREF(mColor));         break; }
      case EBrush::HATCH:   { mHandle = ::CreateHatchBrush(mHatch, COLORREF(mColor)); break; }
      case EBrush::PATTERN: { mHandle = ::CreatePatternBrush(HBITMAP(*mBitmap));      break; }
    }
    return true;
  }
}
