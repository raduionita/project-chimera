#ifndef __glo_ccamera_hpp__
#define __glo_ccamera_hpp__

#include "glo.hpp"

namespace glo {
  class CCamera {
    public:
      void rotate(float yaw, float pitch);
  };
}

#endif //__glo_ccamera_hpp__
