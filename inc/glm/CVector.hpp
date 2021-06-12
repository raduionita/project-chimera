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
        struct { T x, y; };
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
      CVector  operator  -(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs.data[i];
        return result;
      }
      CVector& operator -=(const CVector& rhs) {
        return (*this = *this - rhs);
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
      T    length() { return (T) ::sqrt(x * x + y * y);}
      void normalize() {
        T l = length();
        if (l != T(1)) {
          x /= l;
          y /= l;
        }
      }
  };
  
  template<typename T> class CVector<T,3> {
      template<typename F, const ushort n> friend class CVector;
    public:
      typedef CVector<T, 3> vec_t;
      static const ushort   size = 3;
    public:
      union {
        T data[3];
        struct { T x, y, z; };
        struct { T s, t, p; };
        struct { T r, g, b; };
      };
    public:
      CVector() : x(T(0)), y(T(0)), z(T(0)) {}
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
      CVector  operator  -(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs.data[i];
        return result;
      }
      CVector& operator -=(const CVector& rhs) {
        return (*this = *this - rhs);
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
    public: // operator: cast
      explicit operator       T*()       { return       (T*) (&data[0]); }
      explicit operator const T*() const { return (const T*) (&data[0]); }
            T* operator        *()       noexcept { return data; }
      const T* operator        *() const noexcept { return data; }
    public: 
      T    length() {
        return (T) sqrt(x * x + y * y + z * z);
      }
      void normalize() {
        T l = length();
        if (l != T(1)) {
          x /= l;
          y /= l;
          z /= l;
        }
      }
      // rotate vector to quat orientation
      void rotate(const CQuaterion <T>& Q) {
        *this = Q * (*this);
      }
  };
  
  template<typename T> class CVector<T,4> {
      template<typename F, const ushort n> friend class CVector;
    public:
      typedef CVector<T,4> vec_t;
      static const ushort  size = 4;
    public:
      union {
        T data[4];
        struct { T x, y, z, w; };
        struct { T s, t, p, q; };
        struct { T r, g, b, a; };
      };
    public:
      CVector() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
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
      CVector(const CVector<T,2>& xy, const T z, const T w) {
        data[0] = xy.data[0];
        data[1] = xy.data[1];
        data[2] = z;
        data[3] = w;
      }
      CVector(const T x, const CVector<T,2>& yz, const T w) {
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
      CVector(const CVector<T,3>& xyz, const T w) {
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
      CVector  operator  -(const CVector& rhs) const {
        CVector     result;
        for (ushort i = 0; i < size; i++)
          result.data[i] = data[i] - rhs.data[i];
        return result;
      }
      CVector& operator -=(const CVector& rhs) {
        return (*this = *this - rhs);
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
      T    length() {
        return (T)(std::sqrt(x * x + y * y + z * z + w * w));
      }
      void normalize() {
        T l = length();
        if (l != T(1)) {
          x /= l;
          y /= l;
          z /= l;
          w /= l;
        }
      }
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T, const ushort s> inline const sys::CLogger::ELevel& operator<<(const sys::CLogger::ELevel& type, const CVector<T,s>& v) {
    std::ostringstream os;
    for (ushort        i = 0; i < s; i++)
      os << v[i] << " ";
    sys::CLogger::getSingleton()->push(os.str());
    return type;
  }
  
  template<typename T, const ushort n> const CVector<T, n> operator *(const T s, const CVector<T, n>& v) {
    return v * s;
  }
  
  template<typename T, const ushort n> const CVector<T, n> operator /(const T s, const CVector<T, n>& v) {
    CVector<T, n> out(0);
    for(ushort i = 0; i < n; i++)
      out[i] = s / v[i];
    return out;
  }
  
  template<typename T, const ushort c, const ushort r> CVector<T,c> operator *(const CMatrix<T,c,r>& mat, const CVector<T,r>& vec) {
    CVector<T,c> out(T(0));
    for(ushort i = 0; i < r; i++)
      for(ushort j = 0; j < c; j++)
        out[j] += vec[i] * mat[j][i];
    return out;  
  }
  
  const vec3 O {0.0f, 0.0f, 0.0f};
  const vec3 X {1.0f, 0.0f, 0.0f};
  const vec3 Y {0.0f, 1.0f, 0.0f};
  const vec3 Z {0.0f, 0.0f, 1.0f};
}

#endif //__glm_cvector_hpp__
