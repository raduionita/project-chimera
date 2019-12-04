#ifndef __glm_cmatrix_hpp__
#define __glm_cmatrix_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"
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
    public: // ctors
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
      CMatrix(const CVector<T, r>& vec) {
        for(ushort j = 0; j < c; j++)
          cols[j] = vec;
      }
      CMatrix(const CVector<T, 2>& v0, const CVector<T, 2>& v1) {
        static_assert(r == 2 && c == 2, "Constructor available only for 2x2 CMatrixrices!");
        cols[0] = v0;
        cols[1] = v1;
      }        
      CMatrix(const CVector<T, 3>& v0, const CVector<T, 3>& v1, const CVector<T, 3>& v2) {
        static_assert(r == 3 && c == 3, "Constructor available only for 3x3 CMatrixrices!");
        cols[0] = v0;
        cols[1] = v1;
        cols[2] = v2;
      }
      CMatrix(const CVector<T, 4>& v0, const CVector<T, 4>& v1, const CVector<T, 4>& v2, const CVector<T, 4>& v3) {
        static_assert(r == 4 && c == 4, "Constructor available only for 4x4 CMatrixrices!");
        cols[0] = v0;
        cols[1] = v1;
        cols[2] = v2;
        cols[3] = v3;
      }
      virtual ~CMatrix() { }
    public: // operators: data
      CVector<T, r>&      operator [] (const ushort j)       { return cols[j]; }
      const CVector<T, r> operator [] (const ushort j) const { return cols[j]; }
    public: // operators: math
      CMatrix& operator =  (const CMatrix& that) {
        for(ushort j = 0; j < c; j++)
          for(ushort i = 0; i < r; i++)
            data[j][i] = that.data[j][i];
        return *this;
      }
      CMatrix  operator +  (const CMatrix& that) const {
        CMatrix result;
        for(ushort j = 0; j < c; j++)
          result.data[j] = data[j] + that.data[j];
        return result;  
      }
      CMatrix& operator += (const CMatrix& that) {
        for(ushort j = 0; j < c; j++)
          data[j] += that.data[j];
        return *this;  
      }
      CMatrix  operator -  (const CMatrix& that) const {
        CMatrix result;
        for(ushort j = 0; j < c; j++)
          result.data[j] = data[j] - that.data[j];
        return result;  
      }
      CMatrix& operator -= (const CMatrix& that) {
        for(ushort j = 0; j < c; j++)
          data[j] -= that.data[j];
        return *this;  
      }
      CMatrix  operator *  (const T s) const {
        CMatrix result;
        for(ushort j = 0; j < c; j++)
          result.data[j] = data[j] * s;
        return result;    
      }
      CMatrix& operator *= (const T s) {
        for(ushort j = 0; j < c; j++)
          data[j] = data[j] * s;
        return &this;
      }
      CMatrix  operator *  (const CMatrix& that) const {
        CMatrix result;
        T sum;
        for(ushort j = 0; j < c; j++) {
          for(ushort i = 0; i < r; i++) {
            sum = T(0);
            for(ushort k = 0; k < c; k++)
              sum += data[k][i] * that[j][k];
            result[j][i] = sum;
          }
        }
        return result;
      }
      CMatrix& operator *= (const CMatrix& that) {
        return (*this = *this * that);
      }
      CMatrix  operator /  (const T s) const {
        CMatrix result;
        for(ushort j = 0; j < c; j++)
          result.data[j] = data[j] / s;
        return result;    
      }
      CMatrix& operator /= (const T s) {
        for(ushort j = 0; j < c; j++)
          data[j] = data[j] / s;
        return &this;
      }
      CMatrix  operator /  (const CMatrix& that) const {
        CMatrix result;
        T sum;
        for (ushort j = 0; j < c; j++) {
          for (ushort i = 0; i < r; i++) {
            sum = T(0);
            for(ushort k = 0; k < c; k++)
              sum += data[k][i] / that[j][k];
            result[j][i] = sum;
          }
        }
        return result;
      }
      CMatrix& operator /= (const CMatrix& that) {
        return (*this = *this / that);
      }
    public: // casts  
      explicit inline operator       T* ()       { return       (T*)(&vals[0]); }
      explicit inline operator const T* () const { return (const T*)(&vals[0]); }
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
  
  template <typename T, const ushort c, const ushort r> CVector<T, c> inline operator *(const CVector<T, r>& vec, const CMatrix<T, c, r>& mat) {
    CVector<T, c> result(T(0));
    for(ushort i = 0; i < r; i++)
      for(ushort j = 0; j < c; j++)
        result[j] += vec[i] * mat[j][i];
    return result;  
  }
}

#endif //__glm_cmatrix_hpp__
