#ifndef __glm_cplane_hpp__
#define __glm_cplane_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"

namespace glm {
  template<typename T> class TPlane {
    public:
      union {
        T data[3];
        glm::tvec3<T> normal;
        glm::tvec3<T> n;
        struct { T x,y,z; };
        struct { T a,b,c; };
      }; // vec3  normal // n // (x,y,z) // (a,b,c)
      union {
        T distance;
        T d;
        T w;
      }; // float distance // d // w
    public:
      TPlane() : x{static_cast<T>(0)}, y{static_cast<T>(0)}, z{static_cast<T>(0)}, d{static_cast<T>(0)} { }
      TPlane(T x, T y, T z, T d) : x{x}, y{y}, z{z}, d{d} { }
      /* construct from vec3 & distance */
      TPlane(const glm::tvec3<T>& n, T d) : n{n}, d{d} { normalize(); }
      /* construct from vec4 */
      TPlane(const glm::tvec4<T>& v) : x{v.x}, y{v.y}, z{v.z}, d{v.w} { }
      /* construct from point & normal */
      TPlane(const glm::tvec3<T>& v, const glm::tvec3<T>& n) : n{glm::normalize(n)} { d = /*-*/glm::dot(v,n); }
      /* construct from 3 points */
      TPlane(const glm::tvec3<T>& v0, const glm::tvec3<T>& v1, const glm::tvec3<T>& v2) : n{glm::normalize(glm::cross(v1-v0,v2-v0))}, d{/*-*/glm::dot(v0,n)} { }
      /* copy ctor */
      TPlane(const TPlane& that) : n{that.n}, d{that.d} { }
      /* default destructor */
      ~TPlane() = default;
    public:
      /* assign operator, from glm::plane */
      TPlane&  operator  =(const TPlane& that) { if (this != &that) { n = that.n; d = that.d; } return *this; } 
      /* assign operator, from glm::vec4 */
      TPlane&  operator  =(const glm::tvec4<T>& v) { n = v.xyz; d = v.w; return *this; }
            T& operator [](std::size_t i)       { assert(i < 4); return i == 3 ? d : data[i]; }
      const T& operator [](std::size_t i) const { assert(i < 4); return i == 3 ? d : data[i]; }
      TPlane   operator  /(T s) const { return TPlane{x / s, y / s, z /= s, d /= s}; }
      TPlane&  operator /=(T s)       { x /= s; y /= s; z /= s; d /= s; return *this;} 
    public:
      /* re-init this plane from 3 vertices/vectors */
      inline TPlane& from(const glm::tvec3<T>& v0, const glm::tvec3<T>& v1, const glm::tvec3<T>& v2) { n = glm::normalize(glm::cross(v1-v0,v2-v0)); d = /*-*/glm::dot(v0,n); return *this; }
      /* length of the plane's normal, should be 1 if it's normalized */
      inline T length() const { return std::sqrt(x*x + y*y + z*z); }
      /* normalize this plane */
      inline TPlane& normalize() { T l {length()}; x /= l; y /= l; z /= l; d /= l; return *this; }
    public:
      /* shortest distance form plane to point // glm::dot(p.n, v) + p.d */
      inline T getSignedDistance(const glm::tvec3<T>& v) const { return ((a*v.x) + (b*v.y) + (c*v.z) + d); }
      /* =abs(.getSignedDistance()) */
      inline T getUnsignedDistance(const glm::tvec3<T>& v) const { return std::abs(getSignedDistance(v)); }
      /* glm::vec3 = plane.closestPoint(glm::vec3) // get closes point to v on plane  */
      inline glm::tvec3<T> getClosesPointTo(const glm::tvec3<T>& v) const { return v - (n * getSignedDistance(v)); }
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const TPlane<T>& p) {
    std::ostringstream oss;
    oss << "p[n(" << p.x << ',' << p.y << ',' << p.z << ")," << p.d << ']';
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  template<typename T> inline std::ostream& operator <<(std::ostream& out, const TPlane<T>& p) {
    return out << "p[n(" << p.x << ',' << p.y << ',' << p.z << ")," << p.d << ']';
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  const glm::plane pX {1.0f, 0.0f, 0.0f, 0.f};
  const glm::plane pY {0.0f, 1.0f, 0.0f, 0.f};
  const glm::plane pZ {0.0f, 0.0f, 1.0f, 0.f};
}

#endif //__glm_cplane_hpp__
