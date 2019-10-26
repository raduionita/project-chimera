#ifndef __ogl_cfrustum_hpp__
#define __ogl_cfrustum_hpp__

#include "ogl/ogl.hpp"

namespace ogl {
  class CFrustum { // CMovable, CDrawable
      // @todo: maybe move these to ogl.hpp
      enum class EPlane {
       NEAR   = 0,
       FAR    = 1,
       LEFT   = 2,
       RIGHT  = 3,
       TOP    = 4,
       BOTTOM = 5
      };
      enum class EProjection {
        ORTHOGRAPHIC = 1,
        PERSPECTIVE  = 2,
      };
  };
}

#endif //__ogl_cfrustum_hpp__
