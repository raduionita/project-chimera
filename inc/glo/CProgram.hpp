#ifndef __glo_cprogram_hpp__
#define __glo_cprogram_hpp__

#include "glo.hpp"
#include "CObject.hpp"

namespace glo {
  class CProgram : public CObject {
    public:
      CProgram();
      ~CProgram();
    public:
      inline void bind(bool state = true) const override { GLCALL(::glUseProgram(state ? mID : 0)); }
  };
}

#endif //__glo_cprogram_hpp__
