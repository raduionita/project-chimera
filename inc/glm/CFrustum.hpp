#ifndef __glm_cfrustum_hpp__
#define __glm_cfrustum_hpp__

#include "glm/glm.hpp"
#include "glm/CPlane.hpp"
#include "glm/CAABB.hpp"
#include "glm/CMatrix.hpp"
#include "glm/CVector.hpp"

namespace glm {
  class CFrustum {
    public:
      enum EPlane { LEFT=0, L = LEFT, RIGHT=1, R = RIGHT, BOTTOM=2, B = BOTTOM, TOP=3, T = TOP, NEAR=4, N = NEAR, FAR=5, F = FAR }; // 6
      enum ECorner { LBN = 0, LEFT_BOTTOM_NEAR = LBN, RBN, LTN, RTN, LBF, RBF, LTF, RTF, RIGHT_TOP_FAR = RTF }; // 8
    protected:
      sys::array<glm::plane,6> mPlanes;
      sys::array<glm::vec3,8> mCorners;
    public:
      CFrustum() : mPlanes{} {}
      CFrustum(const glm::mat4& PV) {
        const glm::vec4 row0 {glm::row(PV, 0)};
        const glm::vec4 row1 {glm::row(PV, 1)};
        const glm::vec4 row2 {glm::row(PV, 2)};
        const glm::vec4 row3 {glm::row(PV, 3)};
        // left
        mPlanes[EPlane::LEFT]   = row3 + row0;
        mPlanes[EPlane::LEFT].normalize();
        // right
        mPlanes[EPlane::RIGHT]  = row3 - row0;
        mPlanes[EPlane::RIGHT].normalize();
        // bottom 
        mPlanes[EPlane::BOTTOM] = row3 + row1;
        mPlanes[EPlane::BOTTOM].normalize();
        // top
        mPlanes[EPlane::TOP]    = row3 - row1;
        mPlanes[EPlane::TOP].normalize();
        // near
        mPlanes[EPlane::NEAR]   = row3 + row2;
        mPlanes[EPlane::NEAR].normalize();
        // far
        mPlanes[EPlane::FAR]    = row3 - row2;
        mPlanes[EPlane::FAR].normalize();
        // @from: https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
      }
      CFrustum(const sys::array<glm::vec3,8>& tCorners) : mCorners{tCorners} { }
      ~CFrustum() = default;
    public:
      glm::plane&       operator [](std::size_t i)       { assert(i < 6); return mPlanes[i]; }
      const glm::plane& operator [](std::size_t i) const { assert(i < 6); return mPlanes[i]; }
    public:
      inline const sys::array<glm::vec3,8>&  getCorners() const { return mCorners; }
      inline const sys::array<glm::plane,6>& getPlanes()  const { return mPlanes; }
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /* glm::ECompare = glm::compare(glm::frustum, glm::aabb) // intersection test */
  inline glm::ECompare compare(const glm::frustum& lhs, const glm::aabb& rhs) {
    glm::ECompare rez {glm::ECompare::INSIDE};
    // (temporarly holds min/max relative to plan's normal
    glm::aabb tmp;
    // for each plane
    const auto& all {lhs.getPlanes()};
    for (int i = 0; i < 6; i++) {
      const glm::plane& pln {all[i]}; 
      // x axis
      if (pln.normal.x > 0) {
        tmp.min.x = rhs.min.x;
        tmp.max.x = rhs.max.x;
      } else {
        tmp.min.x = rhs.max.x;
        tmp.max.x = rhs.min.x;
      }
      // y axis
      if (pln.normal.y > 0) {
        tmp.min.y = rhs.min.y;
        tmp.max.y = rhs.max.y;
      } else {
        tmp.min.y = rhs.max.y;
        tmp.max.y = rhs.min.y;
      }
      // z axis
      if (pln.normal.z > 0) {
        tmp.min.z = rhs.min.z;
        tmp.max.z = rhs.max.z;
      } else {
        tmp.min.z = rhs.max.z;
        tmp.max.z = rhs.min.z;
      }
      // compare min (negative far point relative to plane)
      if ((glm::dot(pln.normal, tmp.min) + pln.d) > 0) {
        return glm::ECompare::OUTSIDE;
      }
      // compare max (positive far point relative to plane)
      if ((glm::dot(pln.normal, tmp.max) + pln.d) >= 0) {
        rez = glm::ECompare::INTERSECT;
      }
    } 
    // done
    return rez;
  }
  
  /* glm::frustum = glm::asFrustum(glm::mat4) */
  template<typename T> extern inline glm::frustum asFrustum(const glm::tmat<T,4,4>& M) { return glm::frustum{M}; } 
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const CFrustum& f) {
    std::ostringstream oss;
    oss << "f:" << '\n';
    oss << "L:" << f[CFrustum::L] << '\n';
    oss << "R:" << f[CFrustum::R] << '\n';
    oss << "B:" << f[CFrustum::B] << '\n';
    oss << "T:" << f[CFrustum::T] << '\n';
    oss << "N:" << f[CFrustum::N] << '\n';
    oss << "F:" << f[CFrustum::F];
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  inline std::ostream& operator <<(std::ostream& out, const CFrustum& f) {
    out << "f:" << '\n';
    out << "L:" << f[CFrustum::L] << '\n';
    out << "R:" << f[CFrustum::R] << '\n';
    out << "B:" << f[CFrustum::B] << '\n';
    out << "T:" << f[CFrustum::T] << '\n';
    out << "N:" << f[CFrustum::N] << '\n';
    out << "F:" << f[CFrustum::F];
    return out;
  }
}

#endif //__glm_cfrustum_hpp__
