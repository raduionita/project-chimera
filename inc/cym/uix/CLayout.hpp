#ifndef __cym_uix_clayout_hpp__
#define __cym_uix_clayout_hpp__

#include "uix.hpp"
#include "CObject.hpp"

namespace cym { namespace uix {
  class CLayout : public CObject {
    protected:
      class SItem { CWindow* mItem; };
    public:
      CLayout();
      ~CLayout();
  };
}}

#endif //__cym_uix_clayout_hpp__
