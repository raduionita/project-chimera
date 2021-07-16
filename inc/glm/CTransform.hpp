#ifndef __glm_ctransform_hpp__
#define __glm_ctransform_hpp__

#include "glm/glm.hpp"
#include "glm/CVector.hpp"
#include "glm/CQuaternion.hpp"
#include "glm/CMatrix.hpp"

namespace glm {
  template<typename T> class CTransform {
      static constexpr const T ZERO {static_cast<T>(0)}; 
      static constexpr const T  ONE {static_cast<T>(1)}; 
    public:
      glm::tvec<T,3> position;
      glm::tquat<T>  orientation; 
      glm::tvec<T,3> scale;
    public:
      CTransform() : position{ZERO}, orientation{ONE}, scale{ONE} { }
      CTransform(const T v) : position{v}, orientation{ONE}, scale{ONE} { }
      CTransform(const glm::tvec<T,3>& p) : position{p}, orientation{ONE}, scale{ONE} { }
      CTransform(const glm::tvec<T,3>& p, const glm::tquat<T>& o) : position{p}, orientation{o}, scale{ONE} { }
      CTransform(const glm::tvec<T,3>& p, const glm::tquat<T>& o, const glm::tvec<T,3>& s) : position{p}, orientation{o}, scale{s} { }
      
      CTransform(const glm::tmat<T,4,4>& m) : position{ZERO}, orientation{ONE}, scale{ONE} { 
        
        
// @todo: transfor from CMatrix
        

      }
    public:
      /* xform = xform + xform */
      inline CTransform  operator  +(const CTransform& that) { return CTransform{}; }
      /* xform += xform */
      inline CTransform& operator +=(const CTransform& that) {
        
// @todo: add transforms, make sure resulting pos/orientation/scale is CORRECT
        
        return *this; 
      }
    public:
      inline CTransform<T>& spin() { return *this; }
      inline CTransform<T>& move() { return *this; }
      inline CTransform<T>& grow() { return *this; }
      /* apply transform to vector */
      template<ushort n> inline glm::tvec<T,n> trasform(const glm::tvec<T,n>& v) { return toMatrix() * v; }
    public:
      inline bool isIdentity() const { return (glm::eq(position.x,ZERO) && glm::eq(position.y,ZERO) && glm::eq(position.z,ZERO)) && (glm::eq(orientation.w,ONE) && glm::eq(orientation.x,ZERO) && glm::eq(orientation.y,ZERO) && glm::eq(orientation.z,ZERO)) && (glm::eq(scale.x,ONE) &&& glm::eq(scale.y,ONE) && glm::eq(scale.z,ONE)); }
      inline glm::tmat<T,4,4> toMatrix() const { return glm::translate(position) * glm::asMatrix(orientation) * glm::scale(scale); }
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /* CMatrix::row_t-1 = CTransform * CMatrix::row_t-1 = */
  template<typename T, const ushort n> inline CVector<T,n> operator *(const CTransform<T>& xform, const CVector<T,n>& vec) {
    return xform.toMatrix() * vec;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  template<typename T> inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CTransform<T>& t) {
    std::ostringstream oss;
    oss << "t[p(";
    for (ushort i = 0; i < decltype(t.position)::size; i++)
      oss << t.position[i] << ',';
    oss << "),o(";
    for (ushort i = 0; i < 4; i++)
      oss << t.orientation[i] << ',';
    oss << "),s(";
    for (ushort i = 0; i < decltype(t.scale)::size; i++)
      oss << t.scale[i] << ',';
    oss << ")]";
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  template<typename T> inline std::ostream& operator <<(std::ostream& out, const CTransform<T>& t) {
    out << "t[p(";
    for (ushort i = 0; i < decltype(t.position)::size; i++)
      out << t.position[i] << ',';
    out << "),o(";
    for (ushort i = 0; i < 4; i++)
      out << t.orientation[i] << ',';
    out << "),s(";
    for (ushort i = 0; i < decltype(t.scale)::size; i++)
      out << t.scale[i] << ',';
    out << ")]";
    return out;
  }
}

#endif //__glm_ctransform_hpp__
