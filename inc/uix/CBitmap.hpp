#ifndef __uix_cbitmap_hpp__
#define __uix_cbitmap_hpp__

#include "CGdio.hpp"

namespace uix {
  class CBitmap : public CGdio<HBITMAP> {
    public: // ctor
      CBitmap();
      ~CBitmap(); 
    protected:
      virtual bool init() override;
  };
}

#endif //__uix_cbitmap_hpp__
