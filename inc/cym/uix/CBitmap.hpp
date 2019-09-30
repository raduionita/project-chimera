#ifndef __cym_uix_cbitmap_hpp__
#define __cym_uix_cbitmap_hpp__

#include "CGdio.hpp"

namespace cym::uix {
  class CBitmap : public CGdio<HBITMAP> {
    public: // ctor
      CBitmap();
      ~CBitmap(); 
    protected:
      virtual bool init() override;
  };
}

#endif //__cym_uix_cbitmap_hpp__
