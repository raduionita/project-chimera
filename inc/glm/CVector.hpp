#ifndef __glm_cvector_hpp__
#define __glm_cvector_hpp__

#include "glm/glm.hpp"

namespace glm {
  template <typename T, ushort s> class BVector {
      template <typename F, ushort s1> friend const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel&, const BVector<F,s1>&);
    protected:
      constexpr static ushort size = s; 
  };
  
  template <typename T> class CVector<T,2> : public BVector<T,2> {
      template <typename F, const ushort n>     friend class CVector;
      template <typename F, ushort c, ushort r> friend class CMatrix;
    protected:
      union {
        T data[2];
        struct { T x, y; };
        struct { T s, t; };
        struct { T r, g; };
      };
    public:
      CVector(T v = T(0)) : x(v), y(v) { }
      virtual ~CVector() { }
  };
  
  template <typename T> class CVector<T,3> : public BVector<T,3> {
    protected:
      union {
        T data[3];
        struct { T x, y, z; };
        struct { T s, t, p; };
        struct { T r, g, b; };
      };
    public:
      CVector(T v = T(0)) : x(v), y(v), z(v) { }
      virtual ~CVector() { }
  };
  
  template <typename T> class CVector<T,4> : public BVector<T,4> {
    protected:
      union {
        T data[4];
        struct { T x, y, z, w; };
        struct { T s, t, p, q; };
        struct { T r, g, b, a; };
      };
    public:
      CVector(T v = T(0)) : x(v), y(v), z(v), w(v) { }
      virtual ~CVector() { }
  };
  
  template <typename T, const ushort s> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const BVector<T,s>& m) {
    std::ostringstream os;
    for (ushort i = 0; i < s; i++) {
      os << m.data[i] << " ";
    }
    sys::CLogger::instance()->push(os.str());
    return type;
  }
}

#endif //__glm_cvector_hpp__
