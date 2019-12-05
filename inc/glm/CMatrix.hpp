#ifndef __glm_cmatrix_hpp__
#define __glm_cmatrix_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"
#include "glm/CQuaterion.hpp"
#include "sys/CLogger.hpp"

namespace glm {
  template<typename T, ushort c, ushort r> class CMatrix {
      friend class CMatrix<T,c + 1,r + 1>;
      friend class CMatrix<T,c - 1,r - 1>;
      typedef CMatrix<T,c,r> mat_t;
      typedef CVector<T,r>   vec_t;
    private:
      CVector<T, r> data[c];
    public:
      CMatrix() {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i] = i == j ? T(1) : T(0);
      }
      CMatrix(const CMatrix& that) {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i]  = that.data[j][i];
      }
      explicit CMatrix(const T s) {
        for (ushort j = 0; j < c; j++)
          data[j]     = s;
      }
      CMatrix(const CVector<T,r>& vec) {
        for (ushort j = 0; j < c; j++)
          data[j]     = vec;
      }
      CMatrix(const CVector<T,2>& v0, const CVector<T,2>& v1) {
        static_assert(r == 2 && c == 2, "Constructor available only for 2x2 CMatrixrices!");
        data[0] = v0;
        data[1] = v1;
      }
      CMatrix(const CVector<T,3>& v0, const CVector<T,3>& v1, const CVector<T,3>& v2) {
        static_assert(r == 3 && c == 3, "Constructor available only for 3x3 CMatrixrices!");
        data[0] = v0;
        data[1] = v1;
        data[2] = v2;
      }
      CMatrix(const CVector<T,4>& v0, const CVector<T,4>& v1, const CVector<T,4>& v2, const CVector<T,4>& v3) {
        static_assert(r == 4 && c == 4, "Constructor available only for 4x4 CMatrixrices!");
        data[0] = v0;
        data[1] = v1;
        data[2] = v2;
        data[3] = v3;
      }
    public: // operator: assign
      CMatrix& operator  =(const CMatrix& that) {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i] = that.data[j][i];
        return *this;
      }
    public: // operator: math
      CMatrix operator   +(const CMatrix& that) const {
        CMatrix     result;
        for (ushort j    = 0; j < c; j++)
          result.data[j] = data[j] + that.data[j];
        return result;
      }
      CMatrix& operator +=(const CMatrix& that) {
        for (ushort j = 0; j < c; j++)
          data[j] += that.data[j];
        return *this;
      }
      CMatrix operator   -(const CMatrix& that) const {
        CMatrix     result;
        for (ushort j    = 0; j < c; j++)
          result.data[j] = data[j] - that.data[j];
        return result;
      }
      CMatrix& operator -=(const CMatrix& that) {
        for (ushort j = 0; j < c; j++)
          data[j] -= that.data[j];
        return *this;
      }
      CMatrix operator   *(const T s) const {
        CMatrix     result;
        for (ushort j    = 0; j < c; j++)
          result.data[j] = data[j] * s;
        return result;
      }
      CMatrix& operator *=(const T s) {
        for (ushort j = 0; j < c; j++)
          data[j]     = data[j] * s;
        return &this;
      }
      CMatrix operator   *(const CMatrix& that) const {
        CMatrix     result;
        T           sum;
        for (ushort j = 0; j < c; j++) {
          for (ushort i = 0; i < r; i++) {
            sum = T(0);
            for (ushort k = 0; k < c; k++)
              sum += data[k][i] * that[j][k];
            result[j][i] = sum;
          }
        }
        return result;
      }
      CMatrix& operator *=(const CMatrix& that) {
        return (*this = *this * that);
      }
      CMatrix operator   /(const T s) const {
        CMatrix     result;
        for (ushort j = 0; j < c; j++)
          result.data[j] = data[j] / s;
        return result;
      }
      CMatrix& operator /=(const T s) {
        for (ushort j = 0; j < c; j++)
          data[j]     = data[j] / s;
        return &this;
      }
      CMatrix operator   /(const CMatrix& that) const {
        CMatrix     result;
        T           sum;
        for (ushort j = 0; j < c; j++) {
          for (ushort i = 0; i < r; i++) {
            sum = T(0);
            for (ushort k = 0; k < c; k++)
              sum += data[k][i] / that[j][k];
            result[j][i] = sum;
          }
        }
        return result;
      }
      CMatrix& operator /=(const CMatrix& that) {
        return (*this = *this / that);
      }
    public: // operator: data
      CVector<T,r>&      operator [](const ushort j) {
        return data[j];
      }
      const CVector<T,r> operator [](const ushort j) const {
        return data[j];
      }
    public: // operator: cast
      explicit operator       T*() {
        return (T*) (&data[0]);
      }
      explicit operator const T*() const {
        return (const T*) (&data[0]);
      }
    public:
      CQuaterion<T> asQuaterion() {
        CQuaterion<T> Q;
        /*
        int nxt[3] = { 1, 2, 0 };
        T   s;
        T   tr     = data[0][0] + data[1][1] + data[2][2];
        
        if(tr > 0.0f) // check the diagonal
        {
          s = sqrt(tr + T(1));
          Q.w = s / T(2);
          s = 0.5f / s;
          Q.x = (data[1][2] - data[2][1]) * s;
          Q.y = (data[2][0] - data[0][2]) * s;
          Q.z = (data[0][1] - data[1][0]) * s;
        }
        else // diagonal is negative
        {
          T q[4];
          int i = 0;
          if(data[1][1] > data[0][0]) 
            i = 1;
          if(data[2][2] > data[i][i]) 
            i = 2;
          
          int j = nxt[i];
          int k = nxt[j];
          
          s = sqrt((data[i][i] - (data[j][j] + data[k][k])) + T(1));
          q[i] = s / T(2);
          
          if(s != 0.0f) 
            s = 0.5 / s;
            
          q[3] = (data[j][k] - data[k][j]) * s;
          q[j] = (data[i][j] - data[j][i]) * s;
          q[k] = (data[i][k] - data[k][i]) * s;
          
          Q.x = q[0];
          Q.y = q[1];
          Q.z = q[2];
          Q.w = q[3];
        }
        */
        
        T x2mo = data[0][0] - data[1][1] - data[2][2];  // 4x^2 - 1
        T y2mo = data[1][1] - data[0][0] - data[2][2];
        T z2mo = data[2][2] - data[0][0] - data[1][1];
        T w2mo = data[0][0] + data[1][1] + data[2][2];
        
        int bigestIndex = 0;
        T   b2mo        = w2mo;  // biggest 4*^2-1
        if (x2mo > b2mo) {
          b2mo        = x2mo;
          bigestIndex = 1;
        }
        if (y2mo > b2mo) {
          b2mo        = y2mo;
          bigestIndex = 2;
        }
        if (z2mo > b2mo) {
          b2mo        = z2mo;
          bigestIndex = 3;
        }
        
        T biggestValue = sqrt(b2mo + T(1)) / T(2);
        T mult         = T(0.25) / biggestValue;
        
        switch (bigestIndex) {
          case 0:
            Q.w = biggestValue;
            Q.x = (data[1][2] - data[2][1]) * mult;
            Q.y = (data[2][0] - data[0][2]) * mult;
            Q.z = (data[0][1] - data[1][0]) * mult;
            break;
          case 1:
            Q.w = (data[1][2] - data[2][1]) * mult;
            Q.x = biggestValue;
            Q.y = (data[0][1] - data[1][0]) * mult;
            Q.z = (data[2][0] - data[0][2]) * mult;
            break;
          case 2:
            Q.w = (data[2][0] - data[0][2]) * mult;
            Q.x = (data[0][1] - data[1][0]) * mult;
            Q.y = biggestValue;
            Q.z = (data[1][2] - data[2][1]) * mult;
            break;
          case 3:
            Q.w = (data[0][1] - data[1][0]) * mult;
            Q.x = (data[2][0] - data[0][2]) * mult;
            Q.y = (data[1][2] - data[2][1]) * mult;
            Q.z = biggestValue;
            break;
        }
        
        return Q;
      }
  };
  
  template<typename T, const ushort c, const ushort r>
  inline const sys::CLogger::ELevel& operator<<(const sys::CLogger::ELevel& type, const CMatrix<T, c, r>& m) {
    std::ostringstream os;
    for (ushort        j = 0; j < c; j++) {
      for (ushort i = 0; i < r; i++) {
        os << m.data[i][j] << " ";
      }
      os << '\n';
    }
    sys::CLogger::instance()->push(os.str());
    return type;
  }
  
  template<typename T, const ushort c, const ushort r>
  CVector<T, c> inline operator*(const CVector<T, r>& vec, const CMatrix<T, c, r>& mat) {
    CVector<T, c> result(T(0));
    for (ushort   i = 0; i < r; i++)
      for (ushort j = 0; j < c; j++)
        result[j] += vec[i] * mat[j][i];
    return result;
  }
}

#endif //__glm_cmatrix_hpp__
