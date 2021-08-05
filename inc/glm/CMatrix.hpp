#ifndef __glm_cmatrix_hpp__
#define __glm_cmatrix_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"
#include "glm/CQuaternion.hpp"

namespace glm {
  template<typename T, ushort c, ushort r> class CMatrix {
      friend class CMatrix<T,c + 1,r + 1>;
      friend class CMatrix<T,c - 1,r - 1>;
    public:
      typedef CMatrix<T,c,r> mat_t;
      typedef CVector<T,r>   vec_t;
      typedef CVector<T,c>   row_t;
      typedef CVector<T,r>   col_t;
    private:
      static constexpr const T ZERO {static_cast<T>(0)}; 
      static constexpr const T  ONE {static_cast<T>(1)}; 
      static constexpr const T  TWO {static_cast<T>(2)}; 
      static constexpr const T  EPS {std::numeric_limits<T>::epsilon()}; 
      CVector<T,r> data[c];
    public:
      CMatrix() {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i] = i == j ? ONE : ZERO;
      }
      CMatrix(const CMatrix& that) {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i]  = that.data[j][i];
      }
      explicit CMatrix(const T s) {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i] = i == j ? s : ZERO;
      }
      CMatrix(const glm::tvec<T,r>& vec) {
        for (ushort j = 0; j < c; j++)
          data[j]     = vec;
      }
      CMatrix(const glm::tvec<T,2>& v0, const glm::tvec<T,2>& v1) {
        static_assert(r == 2 && c == 2, "Constructor available only for 2x2 CMatrixrices!");
        data[0] = v0;
        data[1] = v1;
      }
      CMatrix(const glm::tvec<T,3>& c0, const glm::tvec<T,3>& c1, const glm::tvec<T,3>& c2) {
        static_assert(r == 3 && c == 3, "Constructor available only for 3x3 CMatrixrices!");
        data[0] = c0;
        data[1] = c1;
        data[2] = c2;
      }
      CMatrix(const glm::tvec<T,4>& c0, const glm::tvec<T,4>& c1, const glm::tvec<T,4>& c2, const glm::tvec<T,4>& c3) {
        static_assert(r == 4 && c == 4, "Constructor available only for 4x4 CMatrixrices!");
        data[0] = c0; data[1] = c1; data[2] = c2; data[3] = c3;
      }
      CMatrix(const T& c0r0, const T& c0r1, const T& c0r2, const T& c0r3,
              const T& c1r0, const T& c1r1, const T& c1r2, const T& c1r3,
              const T& c2r0, const T& c2r1, const T& c2r2, const T& c2r3,
              const T& c3r0, const T& c3r1, const T& c3r2, const T& c3r3) {
        data[0][0] = c0r0; data[0][1] = c0r1; data[0][2] = c0r2; data[0][3] = c0r3;
        data[1][0] = c1r0; data[1][1] = c1r1; data[1][2] = c1r2; data[1][3] = c1r3;
        data[2][0] = c2r0; data[2][1] = c2r1; data[2][2] = c2r2; data[2][3] = c2r3;
        data[3][0] = c3r0; data[3][1] = c3r1; data[3][2] = c3r2; data[3][3] = c3r3;
      }
    public: // operator: assign
      CMatrix& operator  =(const CMatrix& that) {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i] = that.data[j][i];
        return *this;
      } // operator: assign
      CMatrix& operator  =(T s) {
        for (ushort j = 0; j < c; j++)
          for (ushort i = 0; i < r; i++)
            data[j][i] = s;
        return *this;
      }
    public: // operator: math
      CMatrix  operator  +(const CMatrix& that) const {
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
      CMatrix  operator  -(const CMatrix& that) const {
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
      CMatrix  operator  *(const T s) const {
        CMatrix     result;
        for (ushort j    = 0; j < c; j++)
          result.data[j] = data[j] * s;
        return result;
      }
      CMatrix& operator *=(const T s) {
        for (ushort j = 0; j < c; j++)
          data[j]     = data[j] * s;
        return *this;
      }
      CMatrix  operator  *(const CMatrix& that) const {
        CMatrix out {ZERO};
        T       sum;
        for (ushort ci = 0; ci < c; ci++) {
          // O[ci] = A[0]*B[ci][0] + A[1]*B[ci][1] + A[2]*B[ci][2] + A[3]*B[ci][3];
          // for (ushort ri = 0; ri < r; ri++) {
          //   /*vector*/out[ci] += /*A[ri]=vector=*/data[ri]*/*B[ci][ri]=scalar=*/that.data[ci][ri];
          //   // for (ushort vi = 0; vi < c; vi++) {
          //   //   out[ci][vi] += data[ri][vi] * that.data[ci][ri];
          //   // }
          // }
          for (ushort ri = 0; ri < r; ri++) {
            sum = ZERO;
            // m[0][0] = A[0][0] * B[0][0] +
            for (ushort ii = 0; ii < c; ii++)
              sum += data[ii][ri] * that.data[ci][ii];
            out[ci][ri] = sum;
          }
        }
        return out;
      }
      CMatrix& operator *=(const CMatrix& that) { return (*this = *this * that); }
      CMatrix  operator  /(const T s) const {
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
      CMatrix  operator  /(const CMatrix& that) const {
        CMatrix out;
        T       sum;
        for (ushort ci = 0; ci < c; ci++) {
          for (ushort ri = 0; ri < r; ri++) {
            sum = static_cast<T>(0);
            for (ushort ii = 0; ii < c; ii++)
              sum += data[ii][ri] / that[ci][ii];
            out[ci][ri] = sum;
          }
        }
        return out;
      }
      CMatrix& operator /=(const CMatrix& that) { return (*this = *this / that); }
    // @see CVector.hpp (operator *)
    //CVector<T,r>   operator *(const CVector<T,r>&   vec) const { return vec * *this; } 
    //CVector<T,r-1> operator *(const CVector<T,r-1>& vec) const { return vec * *this; } 
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
      glm::tmat<T,c,r>& identity() {
        *this = glm::ZERO;
        for (ushort j = 0; j < r; j++)
          data[j][j] = glm::ONE;
      }
    public:
      /* glm::quat = glm::mat4::asQuaternion() // to Quaternion */
      glm::tquat<T> asQuaternion() const {
        glm::CQuaternion<T> Q;
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
      /* glm::vec3(pitch, yaw, roll) = glm::mat4::asRotation() */
      glm::tvec3<T> asRotation() const {
        assert(c > 2 && r > 2);
        //    Rx           Ry          Rz
        // |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
        // |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
        // |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
        
        // Pitch: atan(-m[7] / m[8]) = atan(SxCy/CxCy)
        // Yaw  : asin(m[6]) = asin(Sy)
        // Roll : atan(-m[3] / m[0]) = atan(SzCy/CzCy)
        
        T pitch,yaw,roll;
        
        yaw = glm::RAD2DEG * std::asin(data[6]);
        if (data[8] < 0) {
          if (yaw >= 0) {
            yaw =  180.f - yaw; 
          } else {
            yaw = -180.0 - yaw;
          }
        }
        
        if (-std::numeric_limits<T>::epsilon() < data[0] && data[0] < std::numeric_limits<T>::epsilon()) {
          roll = 0;
          pitch = glm::RAD2DEG * std::atan2(data[1],data[4]);
        } else {
          roll  = glm::RAD2DEG * std::atan2(-data[3],data[0]);
          pitch = glm::RAD2DEG * std::atan2(-data[7],data[8]); 
        }
        
        return {pitch,yaw,roll};
      }
  };
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /* CMatrix::col_t = CMatrix::row_t * CMatrix */
  template<typename T, const ushort c, const ushort r> CVector<T,r> inline operator *(const CVector<T,c>& vec, const CMatrix<T,c,r>& mat) {
    // output vector w/ the same no. or rows as the matrix
    
    // mat[3][0] = 10;
    //                                                              //   c
    // glm::tmat<T,4,4>{glm::tvec<T,4> {T(1), T(0), T(0), T(0)},    // r 1 0 0 v0
    //                  glm::tvec<T,4> {T(0), T(1), T(0), T(0)},    //   0 1 0 v1
    //                  glm::tvec<T,4> {T(0), T(0), T(1), T(0)},    //   0 0 1 v2
    //                  glm::tvec<T,4> {v[0], v[1], v[2], T(1)}};   //   0 0 0  1
    
    CVector<T,r> out{T(0)};           // = CMatrix::col_t
    for (ushort i = 0; i < r; i++)    // |M11 M12 ... M1c|   |v1|   |M11*v1 + M12*v2 + ... + M1c*vc|
      for (ushort j = 0; j < c; j++)  // |M21 M22 ... M2c| * |v2| = |M21*v1 ...                    |
        out[i] += vec[j] * mat[j][i]; // |... ... ... ...|   |..|   |...                           |
    return out;                       // |Mr1 Mr2 ... Mrc|   |vc|   |Mr1*v1 + ...... + ... + Mrc*vc|
  }
  
  /* CMatrix::row_t-1 = CMatrix::row_t-1 * CMatrix */
  template<typename T, const ushort c, const ushort r> CVector<T,c-1> inline operator *(const CVector<T,c-1>& vec, const CMatrix<T,c,r>& mat) {
    return CVector<T,c-1>{CVector<T,c>{vec} * mat};
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T, const ushort c, const ushort r> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CMatrix<T,c,r>& m) {
    std::ostringstream oss;
    oss << "m:" << '\n';
    for (ushort   j = 0; j < c; j++) {
      oss << "c(";
      for (ushort i = 0; i < r; i++) {
        oss << m[i][j] << ',';
      }
      oss << ')' << '\n';
    }
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  template<typename T, const ushort c, const ushort r> inline std::ostream& operator <<(std::ostream& out, const CMatrix<T,c,r>& m) {
    out << "m:" << '\n';
    for (ushort   j = 0; j < c; j++) {
      out << "c(";
      for (ushort i = 0; i < r; i++) {
        out << m[i][j] << ',';
      }
      out << ')' << '\n';
    }
    return out;
  }
}

#endif //__glm_cmatrix_hpp__
