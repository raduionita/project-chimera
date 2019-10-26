#ifndef __ogl_cprogram_hpp__
#define __ogl_cprogram_hpp__

#include "ogl.hpp"
#include "CObject.hpp"

namespace ogl {
  class CProgram : public CObject {
    public:
      CProgram();
      ~CProgram();
    public:
      inline void bind(bool state = true) const override { GLCALL(::glUseProgram(state ? mID : 0)); }
  };
}

#endif //__ogl_cprogram_hpp__
