#ifndef __ogl_clight_hpp__
#define __ogl_clight_hpp__

namespace ogl {
  class CLight {
      enum class EType {
        DIRECT,
        POINT, OMNI = POINT
        SPOT,
      };
  };
}

#endif //__ogl_clight_hpp__
