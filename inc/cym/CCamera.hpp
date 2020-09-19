#ifndef __cym_ccamera_hpp__
#define __cym_ccamera_hpp__

#include "cym/cym.hpp"

namespace cym {
  class CCamera {
    protected:
      // glm::quat mOrientation;
      // glm::vec3 mPosition;
    public:
      void rotate(float yaw, float pitch);
  };
}

#endif //__cym_ccamera_hpp__
