#ifndef __glm_cplane_hpp__
#define __glm_cplane_hpp__

#include "glm/glm.hpp"

namespace glm {
  class CPlane : public CShape {
    public:
      uniform {
        struct { glm::vec3 mNormal; real mDistance; };
        struct { glm::vec3 n; real d; };
        struct { glm::vec4 plane; };
      };
  };
}

#endif //__glm_cplane_hpp__
