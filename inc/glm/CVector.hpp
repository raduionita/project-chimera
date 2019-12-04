#ifndef __glm_cvector_hpp__
#define __glm_cvector_hpp__

#include "glm/glm.hpp"

namespace glm {
  template <typename T, ushort s> class CVector { 
      typedef CVector<T, s>  vec_t;
      static const ushort size = s;
  };
  
  template <typename T> class CVector<T,2>;
  template <typename T> class CVector<T,3>;
  template <typename T> class CVector<T,4>;
  
  template <typename T> class CVector<T,2> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CVector<F,s1>&);
      typedef CVector<T, 2>  vec_t;
      static const ushort size = 2;
    public:
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
    public: // operators: assing
      CVector& operator = (const CVector& rhs) {
        for(ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
      CVector& operator = (const T rhs) {
        for(ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
    public: // operators
      T&       operator [] (const ushort i)       { return data[i]; }
      const T& operator [] (const ushort i) const { return data[i]; }
      CVector operator  +  (const CVector& rhs) const {
        CVector result;
        for(ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs.data[i];
        return result;  
      }
      CVector& operator += (const CVector& rhs) {
        return (*this = *this + rhs);
      }
      CVector  operator -  (const CVector& rhs) const {
        CVector result;
        for(ushort i = 0; i < size; i++) 
          result.data[i] = data[i] - rhs.data[i];
        return result;  
      }
      CVector& operator -= (const CVector& rhs) {
        return (*this = *this - rhs);
      }
      CVector  operator -  () const {
        CVector result;
        for(ushort i = 0; i < size; i++) 
          result.data[i] = -data[i];
        return result;  
      }
      CVector  operator /  (const CVector& rhs) const {
        CVector lhs;
        for(ushort i = 0; i < size; i++)
          lhs.data[i] = data[i] / rhs.data[i];
        return lhs;  
      }
      CVector  operator /  (const T rhs) const {
        CVector lhs;
        for(ushort i = 0; i < size; i++)
          lhs.data[i] = data[i] / rhs;
        return lhs;  
      }
      CVector& operator /= (const CVector& rhs) { return (*this = *this / rhs); }
      CVector& operator /= (const T rhs) { return (*this = *this / rhs); }
    public: // casts
      explicit inline operator       T* ()       { return       (T*)(&data[0]); }    
      explicit inline operator const T* () const { return (const T*)(&data[0]); }    
  };
  
  template <typename T> class CVector<T,3> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CVector<F,s1>&);
      typedef CVector<T, 3>  vec_t;
      static const ushort size = 3;
    public:
      union {
        T data[3];
        struct { T x, y, z; };
        struct { T s, t, p; };
        struct { T r, g, b; };
      };
    public: // ctors
      CVector(T v = T(0)) : x(v), y(v), z(v) { }
      CVector(T x, T y) : x(x), y(y), z(T(0)) { }
      CVector(T x, T y, T z) : x(x), y(y), z(z) { }
      CVector(const CVector<T,2>& v) : x(v.x), y(v.y), z(T(0)) { }
      CVector(const CVector<T,3>& v) : x(v.x), y(v.y), z(v.z)  { }
      CVector(const CVector<T,4>& v) : x(v.x), y(v.y), z(v.z)  { }
      virtual ~CVector() { }
    public: // operators: assing
      CVector& operator = (const CVector& rhs) {
        for(ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
      CVector& operator = (const T rhs) {
        for(ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
    public: // operators
      T&       operator [] (const ushort i)       { return data[i]; }
      const T& operator [] (const ushort i) const { return data[i]; }
      CVector operator  +  (const CVector& rhs) const {
        CVector result;
        for(ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs.data[i];
        return result;  
      }
      CVector& operator += (const CVector& rhs) {
        return (*this = *this + rhs);
      }
      CVector  operator -  (const CVector& rhs) const {
        CVector result;
        for(ushort i = 0; i < size; i++) 
          result.data[i] = data[i] - rhs.data[i];
        return result;  
      }
      CVector& operator -= (const CVector& rhs) {
        return (*this = *this - rhs);
      }
      CVector  operator -  () const {
        CVector result;
        for(ushort i = 0; i < size; i++) 
          result.data[i] = -data[i];
        return result;  
      }
      CVector  operator /  (const CVector& rhs) const {
        CVector lhs;
        for(ushort i = 0; i < size; i++)
          lhs.data[i] = data[i] / rhs.data[i];
        return lhs;  
      }
      CVector  operator /  (const T rhs) const {
        CVector lhs;
        for(ushort i = 0; i < size; i++)
          lhs.data[i] = data[i] / rhs;
        return lhs;  
      }
      CVector& operator /= (const CVector& rhs) { return (*this = *this / rhs); }
      CVector& operator /= (const T rhs) { return (*this = *this / rhs); }
    public: // casts
      explicit inline operator       T* ()       { return       (T*)(&data[0]); }    
      explicit inline operator const T* () const { return (const T*)(&data[0]); }    
  };
  
  template <typename T> class CVector<T,4> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const CVector<F,s1>&);
      typedef CVector<T, 4>  vec_t;
      static const ushort size = 4;
    public:
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
    public: // operators: data
      T&       operator [] (const ushort i)       { return data[i]; }
      const T& operator [] (const ushort i) const { return data[i]; }
    public: // operators: assing
      CVector& operator = (const CVector& rhs) {
        for(ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
      CVector& operator = (const T rhs) {
        for(ushort i = 0; i < size; i++)
          data[i] = rhs.data[i];
        return *this;
      }
    public: // operators: math
      CVector operator  +  (const CVector& rhs) const {
        CVector result;
        for(ushort i = 0; i < size; i++)
          result.data[i] = data[i] + rhs.data[i];
        return result;  
      }
      CVector& operator += (const CVector& rhs) {
        return (*this = *this + rhs);
      }
      CVector  operator -  (const CVector& rhs) const {
        CVector result;
        for(ushort i = 0; i < size; i++) 
          result.data[i] = data[i] - rhs.data[i];
        return result;  
      }
      CVector& operator -= (const CVector& rhs) {
        return (*this = *this - rhs);
      }
      CVector  operator -  () const {
        CVector result;
        for(ushort i = 0; i < size; i++) 
          result.data[i] = -data[i];
        return result;  
      }
      CVector  operator /  (const CVector& rhs) const {
        CVector lhs;
        for(ushort i = 0; i < size; i++)
          lhs.data[i] = data[i] / rhs.data[i];
        return lhs;  
      }
      CVector  operator /  (const T rhs) const {
        CVector lhs;
        for(ushort i = 0; i < size; i++)
          lhs.data[i] = data[i] / rhs;
        return lhs;  
      }
      CVector& operator /= (const CVector& rhs) { return (*this = *this / rhs); }
      CVector& operator /= (const T rhs) { return (*this = *this / rhs); }
    public: // casts
      explicit inline operator       T* ()       { return       (T*)(&data[0]); }    
      explicit inline operator const T* () const { return (const T*)(&data[0]); }    
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
