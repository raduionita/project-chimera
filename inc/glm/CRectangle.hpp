#ifndef __glm_crectangle_hpp__
#define __glm_crectangle_hpp__

#include "glm/glm.hpp"
#include "glm/CPlane.hpp"

namespace glm {
  template<typename T> class TRectangle : public TShape<EShape::S2D> {
    public:
      union { 
        struct {T w, h;}; 
        struct {T width, height;};
      };
    public:
      /* from width & height */
      TRectangle(T w, T h) : width{w}, height{h} { }
      /* from plane, using plane's distance */
      TRectangle(const glm::plane& p) : width{p.d}, height{p.d} { }
  };
}

#endif //__glm_crectangle_hpp__
