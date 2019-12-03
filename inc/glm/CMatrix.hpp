#ifndef __glm_cmatrix_hpp__
#define __glm_cmatrix_hpp__

#include "glm/glm.hpp"
#include "sys/CLogger.hpp"

namespace glm {
  template <typename T, ushort c, ushort r> class CMatrix {
      typedef T                val_t;
      typedef CMatrix<T, c, r> mat_t;
      typedef CVector<T, r>    vec_t;
      template <typename F, const ushort n> friend class CVector;
      template <typename F, ushort c1, ushort r1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CMatrix<F,c1,r1>&);
    protected:
      union {
        val_t data[c][r];
        val_t vals[c*r];
        vec_t cols[c];
      };
    public:
      CMatrix() {
        for(ushort j = 0; j < c; j++)
          for(ushort i = 0; i < r; i++)
            data[j][i] = i == j ? T(1) : T(0);
      }
      CMatrix(const CMatrix& that) {
        for(ushort j = 0; j < c; j++)
          for(ushort i = 0; i < r; i++)
            data[j][i] = that.data[j][i]; 
      }
      CMatrix(const T& v) {
        for(ushort j = 0; j < c; j++)
          for(ushort i = 0; i < r; i++)
            data[j][i] = i == j ? v : T(0);
      }
      virtual ~CMatrix() { }
    public: 
      CVector<T, r>&      operator [] (const ushort j)       { return data[j]; }
      const CVector<T, r> operator [] (const ushort j) const { return data[j]; }
      
  };
  
  template <typename T, const ushort c, const ushort r> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CMatrix<T,c,r>& m) {
    std::ostringstream os;
    for (ushort j = 0; j < c; j++) {
      for (ushort i = 0; i < r; i++) {
        os << m.data[i][j] << " ";
      }
      os << '\n';
    }
    sys::CLogger::instance()->push(os.str());
    return type;
  }
}

#endif //__glm_cmatrix_hpp__
