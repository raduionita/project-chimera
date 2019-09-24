#ifndef __cym_uix_cstyle_hpp__ 
#define __cym_uix_cstyle_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CStyle : public CObject {
    protected:
      CBrush*  mBackground {nullptr}; // HBRUSH
      CPen*    mBorder     {nullptr}; // HPEN
      CColor*  mColor      {nullptr};
      CFont*   mFont       {nullptr}; // HFONT
      CCursor* mCursor     {nullptr}; // HCURSOR
      CIcon*   mIcon       {nullptr}; // HICON
    public:
      CStyle(int=ZERO);
      ~CStyle();
    public:
      void    background(CBrush*&&);
      CBrush* background();
  };
}}

#endif //__cym_uix_cstyle_hpp__
