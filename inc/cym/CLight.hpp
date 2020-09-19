#ifndef __cym_clight_hpp__
#define __cym_clight_hpp__

namespace cym {
  class CLight {
      enum class EType {
        DIRECT,
        POINT, OMNI = POINT
        SPOT,
      };
  };
}

#endif //__cym_clight_hpp__
