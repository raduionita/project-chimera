#ifndef __glm_cvector_hpp__
#define __glm_cvector_hpp__

#include "glm/glm.hpp"

namespace glm {
  template <typename T, ushort s> class CVector { };
  template <typename T> class CVector<T,2>;
  template <typename T> class CVector<T,3>;
  template <typename T> class CVector<T,4>;
  
  
  template <typename T> class CVector<T,2> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CVector<F,s1>&);
    protected:
      union {
        T data[2];
        struct { T x, y; };
        struct { T s, t; };
        struct { T r, g; };
      };
    public: // ctors
      CVector(T v = T(0)) : x(v), y(v) { }
      CVector(T x, T y) : x(x), y(y) { }
      CVector(const CVector<T,2>& v) : x(v.x), y(v.y) { }
      CVector(const CVector<T,3>& v) : x(v.x), y(v.y) { }
      CVector(const CVector<T,4>& v) : x(v.x), y(v.y) { }
      virtual ~CVector() { }
    public: // operators
      T&       operator [] (const ushort i)       { return data[i]; }
      const T& operator [] (const ushort i) const { return data[i]; }
      CVector  operator /  (const CVector& rhs) const {
        CVector lhs;
        for(ushort i = 0; i < s; i++)
          lhs.data[i] = data[i] / rhs.data[i];
        return lhs;  
      }
      CVector  operator /  (const T rhs) const {
        CVector lhs;
        for(ushort i = 0; i < s; i++)
          lhs.data[i] = data[i] / rhs;
        return lhs;  
      }
      CVector& operator /= (const CVector& rhs) { return (*this = *this / rhs); }
      CVector& operator /= (const T rhs) { return (*this = *this / rhs); }
  };
  
  template <typename T> class CVector<T,3> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CVector<F,s1>&);
    protected:
      union {
        T data[3];
        struct { T x, y, z; };
        struct { T s, t, p; };
        struct { T r, g, b; };
      };
    public:
      CVector(T v = T(0)) : x(v), y(v), z(v) { }
      CVector(T x, T y) : x(x), y(y), z(T(0)) { }
      CVector(T x, T y, T z) : x(x), y(y), z(z) { }
      CVector(const CVector<T,2>& v) : x(v.x), y(v.y), z(T(0)) { }
      CVector(const CVector<T,3>& v) : x(v.x), y(v.y), z(v.z)  { }
      CVector(const CVector<T,4>& v) : x(v.x), y(v.y), z(v.z)  { }
      virtual ~CVector() { }
    public: // operators
      T&       operator [] (const ushort i)       { return data[i]; }
      const T& operator [] (const ushort i) const { return data[i]; }
      CVector  operator /  (const CVector& rhs) const {
        CVector lhs;
        for(ushort i = 0; i < s; i++)
          lhs.data[i] = data[i] / rhs.data[i];
        return lhs;  
      }
      CVector  operator /  (const T rhs) const {
        CVector lhs;
        for(ushort i = 0; i < s; i++)
          lhs.data[i] = data[i] / rhs;
        return lhs;  
      }
      CVector& operator /= (const CVector& rhs) { return (*this = *this / rhs); }
      CVector& operator /= (const T rhs) { return (*this = *this / rhs); }
  };
  
  template <typename T> class CVector<T,4> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CVector<F,s1>&);
    protected:
      union {
        T data[4];
        struct { T x, y, z, w; };
        struct { T s, t, p, q; };
        struct { T r, g, b, a; };
      };
    public:
      CVector() : x(T(0)), y(T(0)), z(T(0)), w(T(1)) { }
      CVector(T v) : x(v), y(v), z(v), w(v) { }
      CVector(T x, T y) : x(x), y(y), z(T(0)), w(T(1)) { }
      CVector(T x, T y, T z) : x(x), y(y), z(z), w(T(1)) { }
      CVector(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
      CVector(const CVector<T,2>& v) : x(v.x), y(v.y), z(T(0)), w(T(1)) { }
      CVector(const CVector<T,3>& v) : x(v.x), y(v.y), z(v.z),  w(T(1)) { }
      CVector(const CVector<T,4>& v) : x(v.x), y(v.y), z(v.z),  w(v.w)  { }
      virtual ~CVector() { }
    public: // operators
      T&       operator [] (const ushort i)       { return data[i]; }
      const T& operator [] (const ushort i) const { return data[i]; }
      CVector  operator /  (const CVector& rhs) const {
        CVector lhs;
        for(ushort i = 0; i < s; i++)
          lhs.data[i] = data[i] / rhs.data[i];
        return lhs;  
      }
      CVector  operator /  (const T rhs) const {
        CVector lhs;
        for(ushort i = 0; i < s; i++)
          lhs.data[i] = data[i] / rhs;
        return lhs;  
      }
      CVector& operator /= (const CVector& rhs) { return (*this = *this / rhs); }
      CVector& operator /= (const T rhs) { return (*this = *this / rhs); }
  };
  
  template <typename T, const ushort s> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CVector<T,s>& m) {
    std::ostringstream os;
    for (ushort i = 0; i < s; i++) {
      os << m.data[i] << " ";
    }
    sys::CLogger::instance()->push(os.str());
    return type;
  }
  
  const vec3 O {0.0f, 0.0f, 0.0f};
  const vec3 X {1.0f, 0.0f, 0.0f};
  const vec3 Y {0.0f, 1.0f, 0.0f};
  const vec3 Z {0.0f, 0.0f, 1.0f};
}

#endif //__glm_cvector_hpp__
