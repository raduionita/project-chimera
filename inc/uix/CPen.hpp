#ifndef __uix_cpen_hpp__
#define __uix_cpen_hpp__

#include "CGdio.hpp"

namespace uix {
  class CPen : public CGdio<HPEN> {
    public: // ctor
      CPen();
      ~CPen();
    protected:
      virtual bool init() override;
  };
}

#endif //__uix_cpen_hpp__
