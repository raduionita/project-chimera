#ifndef __glm_caabb_hpp__
#define __glm_caabb_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CTransform.hpp"

namespace glm {
  /* axis aligned bounding box // extent // range //  */
  class CAABB {
      using ECompare = glm::ECompare;
    public:
      glm::vec3 min, max;
    public:
      CAABB(glm::real v = static_cast<glm::real>(0)) : min{v}, max{v} { }
      CAABB(glm::real tMin, glm::real tMax) : min{tMin}, max{tMax} { }
      CAABB(const glm::vec3& c, glm::real r) : min{c}, max{c} { glm::real t = r/glm::SQRT_3; min -= t; max += t; }
      CAABB(const glm::vec3 tMin, const glm::vec3 tMax) : min{glm::min(tMin,tMax)}, max{glm::max(tMin,tMax)} { }
      CAABB(glm::real minx, glm::real miny, glm::real minz, glm::real maxx, glm::real maxy, glm::real maxz) : min{minx,miny,minz}, max{maxx,maxy,maxz} { min = glm::min(min,max); max = glm::max(min,max); }
      CAABB(const CAABB& that) : min{glm::min(that.min,that.max)}, max{glm::max(that.min,that.max)} { }
      ~CAABB() = default;
    public:
      inline CAABB&  operator =(const CAABB& rhs) { min = glm::min(rhs.min,rhs.max); max = glm::max(rhs.min,rhs.max); return *this; }
      inline CAABB&  operator =(glm::real v) { min = v; max = v; return *this; }
    public:
      inline CAABB&  operator +=(const CAABB& rhs) { min = glm::min(min,rhs.min); max = glm::max(max,rhs.max); return *this; }
      inline CAABB   operator  +(const CAABB& rhs) { return {glm::min(min,rhs.min), glm::max(max,rhs.max)}; }
    public:
      inline CAABB&  operator *=(const glm::mat4& M) { min = M * min; max = M * max; normalize(); return *this; };
      inline CAABB   operator  *(const glm::mat4& M) { glm::CAABB b{M * min, M * max}; b.normalize(); return b; };
      inline CAABB&  operator *=(const glm::xform& t) { auto M {t.toMatrix()}; min = M * min; max = M * max; normalize(); return *this; };
      inline CAABB   operator  *(const glm::xform& t) { auto M {t.toMatrix()}; glm::aabb b{M * min, M * max}; b.normalize(); return b; };
    public:
      inline bool operator ==(const CAABB& rhs) const { return glm::eq(min.x,rhs.min.x)  && glm::eq(min.y,rhs.min.y)  && glm::eq(min.z,rhs.min.z)  && glm::eq(max.x,rhs.max.x)  && glm::eq(max.y,rhs.max.y)  && glm::eq(max.z,rhs.max.z); }
      inline bool operator !=(const CAABB& rhs) const { return !(*this == rhs); }
      inline bool operator  >(const CAABB& rhs) const { return glm::lt(min.x,rhs.min.x)  && glm::lt(min.y,rhs.min.y)  && glm::lt(min.z,rhs.min.z)  && glm::gt(max.x,rhs.max.x)  && glm::gt(max.y,rhs.max.y)  && glm::gt(max.z,rhs.max.z); }
      inline bool operator >=(const CAABB& rhs) const { return glm::lte(min.x,rhs.min.x) && glm::lte(min.y,rhs.min.y) && glm::lte(min.z,rhs.min.z) && glm::gte(max.x,rhs.max.x) && glm::gte(max.y,rhs.max.y) && glm::gte(max.z,rhs.max.z); }
      inline bool operator  <(const CAABB& rhs) const { return glm::gt(min.x,rhs.min.x)  && glm::gt(min.y,rhs.min.y)  && glm::gt(min.z,rhs.min.z)  && glm::lt(max.x,rhs.max.x)  && glm::lt(max.y,rhs.max.y)  && glm::lt(max.z,rhs.max.z); }
      inline bool operator <=(const CAABB& rhs) const { return glm::gte(min.x,rhs.min.x) && glm::gte(min.y,rhs.min.y) && glm::gte(min.z,rhs.min.z) && glm::lte(max.x,rhs.max.x) && glm::lte(max.y,rhs.max.y) && glm::lte(max.z,rhs.max.z); }
    public:
      /* when min & max = 0 */
      inline bool isZero() const { return min.isZero() && max.isZero(); }
      /* when min > max */
      inline bool isNull() const { return min.x > max.y || min.y > max.y || min.z > max.z; }
      /* min = max */
      inline bool isPoint() const { return glm::eq(min,max); }
      /* diagonal as vector */
      inline glm::vec3 getDiagonal() const { return !isNull() ? (max - min) : glm::vec3(0.f); }
      /* center-position point-vector */
      inline glm::vec3 getCenter() const { return !isNull() ? (min + getDiagonal() * glm::real(0.5f)) : glm::vec3(0.f); }
      /* compute volume{length,height,depth} */
      inline glm::volume getVolume() const { return {max.x-min.x,max.y-min.y,max.z-min.z}; }  
      /* zero AABB, min,max = 0 */
      inline void zero() { min = 0.f; max = 0.f; }
      /* extend AABB by scalar, sub from min, add to max */
      inline void extend(glm::real v) { min -= glm::vec3(v); max += glm::vec3(v); }
      /* extend AABB by point-vector, if point outside AABB, extend it to that point */
      inline void extend(const glm::vec3 p) { min = glm::min(p, min); max = glm::max(p, max); }
      /* extend AABB by another (hopefully external) AABB, using min,max as extension point-vectors */
      inline void extend(const CAABB& that) { extend(that.min); extend(that.max); }
      /* test if that is INSIDE|OUTSIDE|INTERSECTS this */
      inline ECompare compare(const CAABB& that) {
        if (isNull() || that.isNull())
          return ECompare::OUTSIDE;
        
        // that OUTSIDE this // compare axes
        if (glm::gt(min.x, that.max.x) || glm::lt(max.x, that.min.x) ||
            glm::gt(min.y, that.max.y) || glm::lt(max.y, that.min.y) ||
            glm::gt(min.z, that.max.z) || glm::lt(max.z, that.min.z))
          return ECompare::OUTSIDE;
        
        // that INSIDE this // if min is lesser && max is greater
        if (glm::lte(min.x, that.min.x) && glm::gte(max.x, that.max.x) && 
            glm::lte(min.y, that.min.y) && glm::gte(max.y, that.max.y) && 
            glm::lte(min.z, that.min.z) && glm::gte(max.z, that.max.z))
          return ECompare::INSIDE;
        
        // that INTERSECT(s) this
        return ECompare::INTERSECT;
      }
      /* test if this OVERLAP(s) that, =surrounds */
      inline bool overlaps(const CAABB& that) {
        if (isNull() || that.isNull())
          return false;
        
        // if this OVERLAPS that
        if (that.max.x < min.x || max.x < that.min.x)
          return false;
        if (that.max.y < min.y || max.y < that.min.y)
          return false;
        if (that.max.z < min.z || max.z < that.min.z)
          return false;
        
        return true;
      }
      /* apply glm::xform to glm::aabb */
      inline void transform(const glm::xform& tXForm) { auto M {tXForm.toMatrix()}; min = M * min; max = M * max; /* normalize */ normalize(); }
      /* reset min & max // *this = *this */
      inline void normalize() { min = glm::min(min,max); max = glm::max(min,max); }
  };
  
  inline const sys::CLogger::ELevel& operator<<(const sys::CLogger::ELevel& type, const CAABB& aabb) {
    type << "aabb[" << aabb.min << '>' << aabb.max << ']';
    return type;
  }
  
  inline std::ostream& operator <<(std::ostream& out, const CAABB& aabb) {
    out << "aabb[" << aabb.min << '>' << aabb.max << ']';
    return out;
  }
  
  /* glm::aabb = glm::xform * glm::aabb */
  inline glm::aabb operator *(const glm::xform& t, const glm::aabb& a) { const glm::mat4 M{t.toMatrix()}; glm::aabb b{M * a.min, M * a.max}; b.normalize(); return b; };
  
  inline ECompare compare(const glm::aabb& lhs, const glm::aabb& rhs) {
    if (lhs.isNull() || rhs.isNull())
      return ECompare::OUTSIDE;
    
    // that OUTSIDE this // compare axes
    if (glm::gt(lhs.min.x, rhs.max.x) || glm::lt(lhs.max.x, rhs.min.x) ||
        glm::gt(lhs.min.y, rhs.max.y) || glm::lt(lhs.max.y, rhs.min.y) ||
        glm::gt(lhs.min.z, rhs.max.z) || glm::lt(lhs.max.z, rhs.min.z))
      return ECompare::OUTSIDE;
    
    // that INSIDE this // if min is lesser && max is greater
    if (glm::lte(lhs.min.x, rhs.min.x) && glm::gte(lhs.max.x, rhs.max.x) && 
        glm::lte(lhs.min.y, rhs.min.y) && glm::gte(lhs.max.y, rhs.max.y) && 
        glm::lte(lhs.min.z, rhs.min.z) && glm::gte(lhs.max.z, rhs.max.z))
      return ECompare::INSIDE;
    
    // that INTERSECT(s) this
    return ECompare::INTERSECT;
  }
  
  template<typename T> glm::aabb transform(const glm::aabb& a, const glm::txform<T>& t) { const glm::mat4 M{t.toMatrix()}; glm::aabb b{M * a.min, M * a.max}; b.normalize(); return b; }
  
  inline extern glm::aabb normalize(const glm::aabb& a) { glm::aabb b{a}; b.normalize(); return b; }
}

#endif //__glm_caabb_hpp__
