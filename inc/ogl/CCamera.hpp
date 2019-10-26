#ifndef __ogl_ccamera_hpp__
#define __ogl_ccamera_hpp__

#include "ogl/ogl.hpp"

namespace ogl {
  class CCamera {
    protected:
      // glm::quat mOrientation;
      // glm::vec3 mPosition;
    public:
      void rotate(float yaw, float pitch);
  };
}

#endif //__ogl_ccamera_hpp__
