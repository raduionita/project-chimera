#ifndef __glm_cplane_hpp__
#define __glm_cplane_hpp__

#include "glm/glm.hpp"

namespace glm {
  class CPlane : public CShape {
    public:
      GLfloat3 mNormal;
      GLreal   mDistance;
  };
}

#endif //__glm_cplane_hpp__
