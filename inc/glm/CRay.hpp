#ifndef __glm_cray_hpp__
#define __glm_cray_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"

namespace glm {
  template<typename T> class CRay {
    protected:
      glm::tvec<T,3> mOrigin;
      glm::tvec<T,3> mDirection;
    public:
      CRay() : mOrigin{glm::O}, mDirection{glm::Z} { }
      CRay(const glm::tvec<T,3>& o, const glm::tvec<T,3>& d) : mOrigin{o}, mDirection{d} { }
  };
}

#endif //__glm_cray_hpp__
