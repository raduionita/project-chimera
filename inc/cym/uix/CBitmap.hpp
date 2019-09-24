#ifndef __cym_uix_cbitmap_hpp__
#define __cym_uix_cbitmap_hpp__

#include "CObject.hpp"

namespace cym { namespace uix {
  class CBitmap : public CObject {
    protected:
      HBITMAP mHandler {NULL};
    public: // ctor
      CBitmap();
      ~CBitmap();
    public:
      operator       HBITMAP();
      operator const HBITMAP() const;
  };
}}

#endif //__cym_uix_cbitmap_hpp__
