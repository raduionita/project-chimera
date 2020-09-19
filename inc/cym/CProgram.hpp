#ifndef __cym_cprogram_hpp__
#define __cym_cprogram_hpp__

#include "cym/cym.hpp"
#include "CObject.hpp"

namespace cym {
  class CProgram : public CObject {
    public:
      CProgram();
      ~CProgram();
    public:
      inline void bind(bool state = true) const override { GLCALL(::glUseProgram(state ? mID : 0)); }
  };
}

#endif //__cym_cprogram_hpp__
