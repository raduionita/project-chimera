#ifndef __glm_cvector_hpp__
#define __glm_cvector_hpp__

#include "glm/glm.hpp"

namespace glm {
  template<typename T, ushort s> class CVector {
    public:
      typedef CVector<T, s> vec_t;
      static const ushort   size = s;
  };
  
  template<typename T> class CVector<T,2> {
      template<typename F, const ushort n> friend class CVector;
    public:
      typedef CVector<T,2> vec_t;
      static const ushort  size = 2;
    public:
      union {
        T data[2];
        struct { T x, y; }; // x y 
        struct { T s, t; };
        struct { T r, g; };
      };
    public:
      CVector() : x(T(0)), y(T(0)) {
        // nothing
      }
      CVector(const CVector& that) {
        data[0] = that.data[0];
        data[1] = that.data[1];
      }
      CVector(const T s) {
        data[0] = s;
        data[1] = s;
      }
      CVector(const T x, const T y) {
        data[0] = x;
        data[1] = y;
      }
      CVector(const CVector<T,3>& xyz) {
        data[0] = xyz.data[0];
        data[1] = xyz.data[1];
      }
      CVector(const CVector<T,4>& xyzw) {
        data[0] = xyzw.data[0];
        data[1] = xyzw.data[1];
      }
    public: // operator: assignment
      CVector& operator =(const CVector& rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
      CVector& operator =(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i]     = rhs.data[i];
        return *this;
      }
      CVector& operator =(const T rhs[2]) {
        data[0] = rhs[0];
        data[1] = rhs[1];
        return *this;
      }
    public: // operator: data  
            T& operator [](const ushort i) {
        return data[i];
      }
      const T& operator [](const ushort i) const {
        return data[i];
      }
    public: // operator: math
      CVector operator   +(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs.data[i];
        return result;
      }
      CVector& operator +=(const CVector& rhs) {
        return (*this = *this + rhs);
      }
      CVector  operator  +(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs;
        return result;
      }
      CVector& operator +=(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = data[i] + rhs;
        return *this;
      }
      CVector  operator  -(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs.data[i];
        return result;
      }
      CVector& operator -=(const CVector& rhs) {
        return (*this = *this - rhs);
      }
      CVector  operator  -(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs;
        return result;
      }
      CVector& operator -=(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = data[i] - rhs;
        return *this;
      }
      CVector  operator  -() const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = -data[i];
        return result;
      }
      CVector  operator  *(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] * rhs.data[i];
        return result;
      }
      CVector& operator *=(const CVector& rhs) {
        return (*this = *this * rhs);
      }
      CVector  operator  *(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] * rhs;
        return result;
      }
      CVector& operator *=(const T rhs) {
        return (*this = *this * rhs);
      }
      CVector  operator  /(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] / rhs.data[i];
        return result;
      }
      CVector& operator /=(const CVector& rhs) {
        return (*this = *this / rhs);   // assing(*this / rhs);
      }
      CVector  operator  /(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] / rhs;
        return result;
      }
      CVector& operator /=(const T rhs) {
        return (*this = *this / rhs);   // assing(*this / rhs);
      }
      bool     operator  <(const CVector& rhs) const {
        if (x < rhs.x) {
          return true;
        } else if (x == rhs.x) {
          return y < rhs.y;
        }
        return false;
      }
    public: // operator: cast
      explicit operator       T*()       { return       (T*) (&data[0]); }
      explicit operator const T*() const { return (const T*) (&data[0]); }
            T* operator        *()       noexcept { return data; }
      const T* operator        *() const noexcept { return data; }
    public:
      /* length/magnitude */
      inline T    length() const  { return static_cast<T>(std::sqrt(x*x + y*y));}
      /* normalize */
      inline void normalize() { T l {length()}; x /= l; y /= l; }
      // is zero
      inline bool isZero() const { return glm::eq(x,static_cast<T>(0)) && glm::eq(y,static_cast<T>(0)); }
  };
  
  template<typename T> class CVector<T,3> {
      template<typename F, const ushort n> friend class CVector;
    public:
      typedef CVector<T, 3> vec_t;
      static const ushort   size = 3;
    public:
      union {
        T data[3];
        struct {
          union { 
            struct { T x, y; }; 
            CVector<T,2> xy; 
          }; // x,y 
          T z; 
        }; // x u z
        struct { T s, t, p; };
        struct { T r, g, b; };
      };
    public:
      CVector() : x{T(0)}, y{T(0)}, z{T(0)} {}
      CVector(const T s) : x{s}, y{s}, z{s} { }
      CVector(const T x, const T y, const T z) : x{x}, y{y}, z{z} { }
      CVector(const CVector& xyz) : x{xyz.x}, y{xyz.y}, z{xyz.z} { }
      CVector(const CVector<T,2>& xy, const T z) {
        data[0] = xy.data[0];
        data[1] = xy.data[1];
        data[2] = z;
      }
      CVector(const T x, const CVector<T,2>& yz) {
        data[0] = x;
        data[1] = yz.data[1];
        data[2] = yz.data[2];
      }
      CVector(const CVector<T,4>& xyzw) {
        data[0] = xyzw.data[0];
        data[1] = xyzw.data[1];
        data[2] = xyzw.data[2];
      }      
    public: // operator: assign
      CVector& operator  =(const CVector& rhs) {
        if (this != &rhs)
          for (ushort i = 0; i < size; i++)
            data[i] = rhs.data[i];
        return *this;
      }
      CVector& operator  =(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i]     = rhs;
        return *this;
      }
      CVector& operator =(const T rhs[3]) {
        data[0] = rhs[0];
        data[1] = rhs[1];
        data[2] = rhs[2];
        return *this;
      }
    public: // operator: data  
            T& operator [](ushort i)       { return data[i]; }
      const T& operator [](ushort i) const { return data[i]; }
    public: // operator: math  
      CVector  operator  +(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs.data[i];
        return result;
      }
      CVector& operator +=(const CVector& rhs) {
        return (*this = *this + rhs);
      }
      CVector  operator  +(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs;
        return result;
      }
      CVector& operator +=(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = data[i] + rhs;
        return *this;
      }
      CVector  operator  -(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs.data[i];
        return result;
      }
      CVector& operator -=(const CVector& rhs) {
        return (*this = *this - rhs);
      }
      CVector  operator  -(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs;
        return result;
      }
      CVector& operator -=(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = data[i] - rhs;
        return *this;
      }
      CVector  operator  -() const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = -data[i];
        return result;
      }
      CVector  operator  *(const CVector& rhs) const {
        CVector out;
        for (ushort i = 0; i < size; i++)
          out.data[i] = data[i] * rhs.data[i];
        return out;
      }
      CVector& operator *=(const CVector& rhs) {
        return (*this = *this * rhs);
      }
      CVector  operator  *(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] * rhs;
        return result;
      }
      CVector& operator *=(const T rhs) {
        return (*this = *this * rhs);
      }
      CVector  operator  /(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] / rhs.data[i];
        return result;
      }
      CVector& operator /=(const CVector& rhs) {
        return (*this = *this / rhs);   // assing(*this / rhs);
      }
      CVector  operator  /(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] / rhs;
        return result;
      }
      CVector& operator /=(const T rhs) {
        return (*this = *this / rhs);   // assing(*this / rhs);
      }
      bool     operator  <(const CVector& rhs) const {
        if (x < rhs.x) {
          return true;
        } else if (x == rhs.x) {
          if (y < rhs.y) {
            return true;
          } else if (y == rhs.y) {
            return z < rhs.z;
          }
        }
        return false;
      }
      bool     operator  >=(const CVector& rhs) const {
        if (x >= rhs.x) {
          return true;
        } else if (x == rhs.x) {
          if (y < rhs.y) {
            return true;
          } else if (y == rhs.y) {
            return z < rhs.z;
          }
        }
        return false;
      }
    public: // operator: cast
      explicit operator       T*()       { return       (T*) (&data[0]); }
      explicit operator const T*() const { return (const T*) (&data[0]); }
            T* operator        *()       noexcept { return data; }
      const T* operator        *() const noexcept { return data; }
    public:
      /* length/magnitude */
      inline T    length() const { return static_cast<T>(std::sqrt(x*x + y*y + z*z)); }
      /* normalize */
      inline void normalize() { T l {length()}; x /= l; y /= l; z /= l; }
      /* rotate vector to quat orientation */
      inline void rotate(const glm::tquat<T>& Q) { *this = Q * (*this); }
      /* is zero */
      inline bool isZero() const { return glm::eq(x,static_cast<T>(0)) && glm::eq(y,static_cast<T>(0)) && glm::eq(z,static_cast<T>(0)); }
  };
  
  template<typename T> class CVector<T,4> {
      template<typename F, const ushort n> friend class CVector;
    public:
      typedef CVector<T,4> vec_t;
      static const ushort  size = 4;
    public:
      union {
        T data[4];
        struct {
          union { 
            struct {
              union {
                struct { T x,y; }; // xy
                CVector<T,2> xy;
              };
              T z;
            }; 
            CVector<T,3> xyz; 
          }; // x,y,z 
          T w; 
        }; // x y z w
        struct { T s, t, p, q; };
        struct { T r, g, b, a; };
      };
    public:
      CVector() : x{T(0)}, y{T(0)}, z{T(0)}, w{T(1)} {}
      CVector(const CVector& that) {
        for (ushort i = 0; i < size; i++)
          data[i] = that.data[i];
      }
      CVector(const T s) {
        for (ushort i = 0; i < size; i++)
          data[i]     = s;
      }
      CVector(const T x, const T y, const T z, const T w) {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
      }
      CVector(const CVector<T,2>& xy, const T z = 0, const T w = 1) {
        data[0] = xy.data[0];
        data[1] = xy.data[1];
        data[2] = z;
        data[3] = w;
      }
      CVector(const T x, const CVector<T,2>& yz, const T w = 1) {
        data[0] = x;
        data[1] = yz.data[1];
        data[2] = yz.data[2];
        data[3] = w;
      }
      CVector(const T x, const T y, const CVector<T,2>& zw) {
        data[0] = x;
        data[1] = y;
        data[2] = zw.data[2];
        data[3] = zw.data[3];
      }
      CVector(const CVector<T,3>& xyz, const T w = 1) {
        data[0] = xyz.data[0];
        data[1] = xyz.data[1];
        data[2] = xyz.data[2];
        data[3] = w;
      }
      CVector(const T x, const CVector<T,3>& yzw) {
        data[0] = x;
        data[1] = yzw.data[1];
        data[2] = yzw.data[2];
        data[3] = yzw.data[3];
      }
    public: // operator: assign
      CVector& operator  =(const CVector& rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
      CVector& operator  =(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i]     = rhs;
        return *this;
      }
      CVector& operator =(const T rhs[4]) {
        data[0] = rhs[0];
        data[1] = rhs[1];
        data[2] = rhs[2];
        data[4] = rhs[4];
        return *this;
      }
    public: // operator: data
            T& operator [](const ushort i) {
        return data[i];
      }
      const T& operator [](const ushort i) const {
        return data[i];
      }
    public: // operator: math  
      CVector  operator  +(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs.data[i];
        return result;
      }
      CVector& operator +=(const CVector& rhs) {
        return (*this = *this + rhs);
      }
      CVector  operator  +(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs;
        return result;
      }
      CVector& operator +=(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = data[i] + rhs;
        return *this;
      }
      CVector  operator  -(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs.data[i];
        return result;
      }
      CVector& operator -=(const CVector& rhs) {
        return (*this = *this - rhs);
      }
      CVector  operator  -(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs;
        return result;
      }
      CVector& operator -=(const T rhs) {
        for (ushort i = 0; i < size; i++)
          data[i] = data[i] - rhs;
        return *this;
      }
      CVector  operator  -() const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = -data[i];
        return result;
      }
      CVector  operator  *(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] * rhs.data[i];
        return result;
      }
      CVector& operator *=(const CVector& rhs) {
        return (*this = *this * rhs);
      }
      CVector  operator  *(const T rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] * rhs;
        return result;
      }
      CVector& operator *=(const T rhs) {
        return (*this = *this * rhs);
      }
      CVector  operator  /(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] / rhs.data[i];
        return result;
      }
      CVector& operator /=(const CVector& rhs) {
        return (*this = *this / rhs);   // assing(*this / rhs);
      }
      CVector  operator  /(const T rhs) const {
        CVector<T,size> result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] / rhs;
        return result;
      }
      CVector& operator /=(const T rhs) {
        return (*this = *this / rhs);   // assing(*this / rhs);
      }
    public: // operator: bool
      bool     operator  <(const CVector& rhs) const {
        if (x < rhs.x)                       // TODO: use math::greater()
        {
          return true;
        } else if (x == rhs.x)                 // TODO: use math::equals()
        {
          if (y < rhs.y) {
            return true;
          } else if (y == rhs.y) {
            if (z < rhs.z) {
              return true;
            } else if (z == rhs.z) {
              return w < rhs.w;
            }
          }
        }
        return false;
      }
    public: // operator: cast
      explicit operator       T*()       { return       (T*)(&data[0]); }
      explicit operator const T*() const { return (const T*)(&data[0]); }
            T* operator        *()       noexcept { return data; }
      const T* operator        *() const noexcept { return data; }
    public:
      /* length/magnitude */
      inline T    length() const { return static_cast<T>(std::sqrt(x*x + y*y + z*z + w*w)); }
      /* normalize */
      inline void normalize() { T l {length()}; x /= l; y /= l; z /= l; w /= l; }
      // is zero
      inline bool isZero() const { return glm::eq(x,static_cast<T>(0)) && glm::eq(y,static_cast<T>(0)) && glm::eq(z,static_cast<T>(0)) && glm::eq(w,static_cast<T>(0)); }
  };
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T, const ushort n> inline const CVector<T,n> operator *(const T s, const CVector<T,n>& v) {
    return v * s;
  }
  
  template<typename T, const ushort n> inline const CVector<T,n> operator /(const T s, const CVector<T,n>& v) {
    CVector<T, n> out(0);
    for(ushort i = 0; i < n; i++)
      out[i] = s / v[i];
    return out;
  }
  
  /* CMatrix::col_t = CMatrix * CMatrix::row_t = */
  template<typename T, const ushort c, const ushort r> inline CVector<T,r> operator *(const CMatrix<T,c,r>& mat, const CVector<T,c>& vec) {
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
  
  /* CMatrix::row_t-1 = CMatrix * CMatrix::row_t-1 = */
  template<typename T, const ushort c, const ushort r> inline CVector<T,c-1> operator *(const CMatrix<T,c,r>& mat, const CVector<T,c-1>& vec) {
    return CVector<T,c-1>{mat * CVector<T,c>{vec}};
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T, const ushort s> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CVector<T,s>& v) {
    std::ostringstream oss;
    oss << "v(";
    for (ushort        i = 0; i < s; i++)
      oss << v[i] << ',';
    oss << ')';
    sys::CLogger::push(oss.str());
    return type;
  }  
  
  template<typename T, const ushort s> inline std::ostream& operator <<(std::ostream& out, const CVector<T,s>& v) {
    out << "v(";
    for (ushort        i = 0; i < s; i++)
      out << v[i] << ',';
    out << ')';
    return out;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const glm::vec3 O {0.0f, 0.0f, 0.0f};
  const glm::vec3 X {1.0f, 0.0f, 0.0f};
  const glm::vec3 Y {0.0f, 1.0f, 0.0f};
  const glm::vec3 Z {0.0f, 0.0f, 1.0f};
}

#endif //__glm_cvector_hpp__
