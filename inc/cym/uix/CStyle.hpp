#ifndef __cym_uix_cstyle_hpp__ 
#define __cym_uix_cstyle_hpp__

#include "CObject.hpp"
#include "CBrush.hpp"

namespace cym { namespace uix {
  class CStyle : public CObject {
    protected:
      CBrush*  mBackground {nullptr}; // HBRUSH
      CPen*    mBorder     {nullptr}; // HPEN
      SColor*  mColor      {nullptr};
      CFont*   mFont       {nullptr}; // HFONT
      CCursor* mCursor     {nullptr}; // HCURSOR
      CIcon*   mIcon       {nullptr}; // HICON
    public:
      CStyle(int=ZERO);
      ~CStyle();
    public:
      void    background(CBrush*&&);
      CBrush* background();
    public:
      static CStyle* merge(CStyle* lhs, CStyle* rhs); 
  };
}}

#endif //__cym_uix_cstyle_hpp__
