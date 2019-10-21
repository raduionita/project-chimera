#ifndef __glo_cfrustum_hpp__
#define __glo_cfrustum_hpp__

#include "glo/glo.hpp"

namespace glo {
  class CFrustum { // CMovable, CDrawable
      // @todo: maybe move these to glo.hpp
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

#endif //__glo_cfrustum_hpp__
