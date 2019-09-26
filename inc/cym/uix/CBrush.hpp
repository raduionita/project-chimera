#ifndef __cym_uix_cbrush_hpp__
#define __cym_uix_cbrush_hpp__

#include "CGdio.hpp"

namespace cym { namespace uix {
  enum class EBrush {
    SOLID   = 1,
    HATCH   = 2,
    PATTERN = 3,
  };
  
  class CBrush : public CGdio<HBRUSH> {
    protected:
      EBrush    mType   {EBrush::SOLID};
      int       mHatch  {0};
      SColor    mColor  {0};
      CBitmap*  mBitmap {nullptr};
    public: // ctor
      CBrush();
      CBrush(SColor&& sColor) : mColor{std::move(sColor)} {}
      CBrush(SColor&& sColor, int&& nHatch) : mColor{std::move(sColor)}, mHatch{nHatch} { }
      CBrush(CBitmap*&& pBitmap) : mBitmap{std::move(pBitmap)} { } 
      ~CBrush();
    protected:
      virtual bool init() override;
  };
}}

#endif //__cym_uix_cbrush_hpp__
