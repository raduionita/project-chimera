#ifndef __cym_uix_cstyle_hpp__ 
#define __cym_uix_cstyle_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CStyle : public CObject {
    protected:
      
      CBrush* mBackground {nullptr};
    public:
      CStyle();
      ~CStyle();
    public:
      void    background(CBrush*);
      CBrush* background();
  };
}}

#endif //__cym_uix_cstyle_hpp__
