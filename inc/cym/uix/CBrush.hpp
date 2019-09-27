#ifndef __cym_uix_cbrush_hpp__
#define __cym_uix_cbrush_hpp__

#include "CGdio.hpp"

namespace cym { namespace uix {
  enum class EBrush {
    NONE    = 0,
    SOLID   = 1,
    HATCH   = 2,
    PATTERN = 3,
  };
  
  class CBrush : public CGdio<HBRUSH> {
      using CGdio<HBRUSH>::CGdio;
    protected:
      EBrush    mType   {EBrush::NONE};
      int       mHatch  {0};
      SColor    mColor  {0};
      CBitmap*  mBitmap {nullptr};
    public: // ctor
      CBrush();
      CBrush(SColor&&);
      CBrush(SColor&&, int&&);
      CBrush(CBitmap*&&); 
      ~CBrush();
    protected:
      virtual bool init() override;
  };
}}

#endif //__cym_uix_cbrush_hpp__
