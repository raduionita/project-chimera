#ifndef __gls_cplane_hpp__
#define __gls_cplane_hpp__

#include "gls.hpp"

namespace gls {
  class CPlane : public CShape {
    public:
      GLfloat3 mNormal;
      GLreal   mDistance;
  };
}

#endif //__gls_cplane_hpp__
