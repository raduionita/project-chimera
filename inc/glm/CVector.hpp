#ifndef __glm_cvector_hpp__
#define __glm_cvector_hpp__

#include "glm/glm.hpp"

namespace glm {
  template <typename T> class CVector<T,2> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
    protected:
      union {
        T data[2];
        struct { T x; T y; };
        struct { T s; T t; };
        struct { T r; T g; };
      };
  };
}

#endif //__glm_cvector_hpp__
