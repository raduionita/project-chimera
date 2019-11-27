#ifndef __glm_cmatrix_hpp__
#define __glm_cmatrix_hpp__

#include "glm/glm.hpp"

namespace glm {
  template <typename T, ushort c, ushort r> class CMatrix {
      typedef T                val_t;
      typedef CMatrix<T, c, r> mat_t;
      typedef CVector<T, r>    vec_t;
      template <typename F, const ushort n> friend class CVector;
    protected:
      union {
        val_t rows[c][r];
        val_t data[c*r];
        vec_t vecs[c];
      };
  };
}

#endif //__glm_cmatrix_hpp__
