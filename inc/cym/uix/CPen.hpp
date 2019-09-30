#ifndef __cym_uix_cpen_hpp__
#define __cym_uix_cpen_hpp__

#include "CGdio.hpp"

namespace cym::uix {
  class CPen : public CGdio<HPEN> {
    public: // ctor
      CPen();
      ~CPen();
    protected:
      virtual bool init() override;
  };
}

#endif //__cym_uix_cpen_hpp__
