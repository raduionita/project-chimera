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
      using EPlane  = glm::EPlane; // 6
      using ECorner = glm::ECorner; // 8
    protected:
      sys::array<glm::plane,6> mPlanes;
    public:
      CFrustum() {}
      CFrustum(const glm::mat4& PV) {
        sys::array<glm::plane,6>& tPlanes {mPlanes};
        // extract rows
        const glm::vec4 row0 {glm::row(PV, 0)};
        const glm::vec4 row1 {glm::row(PV, 1)};
        const glm::vec4 row2 {glm::row(PV, 2)};
        const glm::vec4 row3 {glm::row(PV, 3)};
        // @from: https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf
        tPlanes[EPlane::LEFT] = row3 + row0;
        tPlanes[EPlane::LEFT].normalize();
        // right
        tPlanes[EPlane::RIGHT] = row3 - row0;
        tPlanes[EPlane::RIGHT].normalize();
        // bottom 
        tPlanes[EPlane::BOTTOM] = row3 + row1;
        tPlanes[EPlane::BOTTOM].normalize();
        // top
        tPlanes[EPlane::TOP] = row3 - row1;
        tPlanes[EPlane::TOP].normalize();
        // near
        tPlanes[EPlane::NEAR] = row3 + row2;
        tPlanes[EPlane::NEAR].normalize();
        // far
        tPlanes[EPlane::FAR] = row3 - row2;
        tPlanes[EPlane::FAR].normalize();
        
        // BOOL cMap::GetIntersection (int a, int b, int c, D3DXPLANE *Plane, D3DXPLANE *Plane2, D3DXPLANE *Plane3, float &X, float &Y, float &Z) {	
        //   D3DXVECTOR3 Normal = (&Plane->a, &Plane->b, &Plane->c);	
        //   D3DXVECTOR3 Normal2 = (&Plane2->a, &Plane2->b, &Plane2->c);	
        //   D3DXVECTOR3 Normal3 = (&Plane3->a, &Plane3->b, &Plane3->c);	
        //   D3DXVECTOR3 CrossProduct;	
        //   D3DXVECTOR3 CrossProduct2;	
        //   D3DXVECTOR3 CrossProduct3;	
        //   D3DXVECTOR3 DotProduct;	
        //   float DotProduct2;	
        //   float DotProduct3;	
        //   D3DXVECTOR3 IntersectCoordinate;	
        //   D3DXVECTOR3 Num1; 
        //   D3DXVECTOR3 Num2;
        //   D3DXVECTOR3 Num3;
        //   D3DXVec3Cross( &CrossProduct , &Normal2 , &Normal3 );	
        //   D3DXVec3Cross( &CrossProduct2 , &Normal3 , &Normal );	
        //   D3DXVec3Cross( &CrossProduct3 , &Normal , &Normal2 );		
          //   //X = 0;	//Y = 0;	//Z = 0;	//DotProduct = D3DXPlaneDotCoord(Plane, &D3DXVECTOR3(X,Y,Z));	
          //   // DotProduct2 = D3DXPlaneDotCoord(Plane2, &D3DXVECTOR3(X,Y,Z));	
          //   // DotProduct3 = D3DXPlaneDotCoord(Plane3, &D3DXVECTOR3(X,Y,Z));	
        //   float XPos;	float YPos;	float ZPos;	
        //   float denom = D3DXVec3Dot (&Normal, &CrossProduct);	
        //   if( denom == 0 ) {		return FALSE;	}		
        //   Num1 = -(Plane->d * CrossProduct);	
        //   Num2 = -(Plane2->d * CrossProduct2);	
        //   Num3 = -(Plane3->d * CrossProduct3);		
        //   IntersectCoordinate =  (Num1 + Num2 + Num3) / denom;	
        //  
        //   X = IntersectCoordinate.x;	
        //   Y = IntersectCoordinate.y;	
        //   Z = IntersectCoordinate.z;	
          //   //XPos = (D3DXPlaneDotCoord(Plane, &D3DXVECTOR3(X,Y,Z)));	
          //   //YPos = (D3DXPlaneDotCoord(Plane2, &D3DXVECTOR3(X,Y,Z)));	
          //   //ZPos = (D3DXPlaneDotCoord(Plane3, &D3DXVECTOR3(X,Y,Z)));		
          //   // X = XPos;	
          //   // Y = YPos;	
          //   // Z = ZPos;	
          //   // X *= -1;	
          //   // Y *= -1;	
          //   // Z *= -1.0f;	
        //   return TRUE;
        // }    
      }
      CFrustum(const sys::array<glm::vec3,8>& tCorners) {
        mPlanes[EPlane::L].from(tCorners[LTF], tCorners[LBF], tCorners[LBN]);
        mPlanes[EPlane::R].from(tCorners[RTN], tCorners[RBN], tCorners[RBF]);
        mPlanes[EPlane::B].from(tCorners[RBF], tCorners[RBN], tCorners[LBN]);
        mPlanes[EPlane::T].from(tCorners[RTN], tCorners[RTF], tCorners[LTF]);
        mPlanes[EPlane::F].from(tCorners[RTF], tCorners[RBF], tCorners[LBF]);
        mPlanes[EPlane::N].from(tCorners[LTN], tCorners[LBN], tCorners[RBN]);
        // SYS_LOG_NFO("glm::CFrustum::CFrustum(sys::array<glm::vec3,8>&)" << " corners:" << tCorners << "\nplanes:" << mPlanes);
      }
      ~CFrustum() = default;
    public:
      glm::plane&       operator [](std::size_t i)       { assert(i < 6); return mPlanes[i]; }
      const glm::plane& operator [](std::size_t i) const { assert(i < 6); return mPlanes[i]; }
    public:
      /* = glm::frustum.getPlanes() */
      inline const sys::array<glm::plane,6>& getPlanes() const { return mPlanes; }
      /* = glm::frustum.getCorners() */
      sys::array<glm::vec3,8>  getCorners() const { 
        sys::array<glm::vec3,8> tCorners;
        //  n1 * n2 x n3 != 0 =>  
        static const int kCorners[8][3] {/*LBN*/{LEFT,BOTTOM,NEAR},/*RBN*/{RIGHT,BOTTOM,NEAR},/*LTN*/{LEFT,TOP,NEAR},/*RTN*/{RIGHT,TOP,NEAR},/*LBF*/{LEFT,BOTTOM,FAR},/*RBF*/{RIGHT,BOTTOM,FAR},/*LTF*/{LEFT,TOP,FAR},/*RTF*/{RIGHT,TOP,FAR}};
        // for each corner
        for (uint i = 0; i < 8; i++) {
          // A1x + B1y + C1z + D1 = 0
          // A2x + B2y + C2z + D2 = 0
          // A3x + B3y + C3z + D3 = 0
          const glm::plane& P1 {mPlanes[kCorners[i][0]]}; // LEFT
          const glm::plane& P2 {mPlanes[kCorners[i][1]]}; // BOTTOM
          const glm::plane& P3 {mPlanes[kCorners[i][2]]}; // NEAR
          
          // n1 * (n2 x n3) != 0 // has an intersection point (corner) // if (glm::dot(n1,glm::cross(n2,n3)) != 0) ... 
          
          // apply cramer's rule
          // http://www.ambrsoft.com/TrigoCalc/Plan3D/3PlanesIntersection_.htm
          
          //       | A1 B1 C1| 
          // det = | A2 B2 C2| != 0 
          //       | A3 B3 C3|
          const glm::real d {/*(-1)**/glm::det(glm::mat3{P1.n, P2.n, P3.n})};
          
 // @todo: find why (-1) is needed //seems xyz have inversed signes // maybe it's because the n of the planes
          
          // ref
          glm::vec3& tCorner {tCorners[i]};
          //     | D1 B1 C1 |
          // x = | D2 B2 C2 | / det
          //     | D3 B3 C3 |
          tCorner.x = glm::det(glm::mat3{glm::vec3{ P1.d, P2.d, P3.d }, 
                                         glm::vec3{ P1.b, P2.b, P3.b }, 
                                         glm::vec3{ P1.c, P2.c, P3.c }}) / d;
          //     | A1 D1 C1 |
          // y = | A2 D2 C2 | / det
          //     | A3 D3 C3 | 
          tCorner.y = glm::det(glm::mat3{glm::vec3{ P1.a, P2.a, P3.a }, 
                                         glm::vec3{ P1.d, P2.d, P3.d }, 
                                         glm::vec3{ P1.c, P2.c, P3.c }}) / d;
          //     | A1 B1 D1 |
          // z = | A2 B2 D2 | / det
          //     | A3 B3 D3 | 
          tCorner.z = glm::det(glm::mat3{glm::vec3{ P1.a, P2.a, P3.a }, 
                                         glm::vec3{ P1.b, P2.b, P3.b }, 
                                         glm::vec3{ P1.d, P2.d, P3.d }}) / d;
          
// @todo: reduce the need for glm::det & glm::mat3
        }
        return tCorners;
      }
  };
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /* glm::ECompare = glm::compare(glm::frustum, glm::aabb) // intersection test */
  inline glm::ECompare compare(const glm::frustum& lhs, const glm::aabb& rhs) {
    glm::ECompare rez {glm::ECompare::INSIDE};
    // (temporarly holds min/max relative to plan's normal
    glm::aabb tmp;
    // for each plane
    const auto all {lhs.getPlanes()};
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
    oss << "f{" << '\n';
    oss << "L:" << f[EPlane::LEFT]   << '\n';
    oss << "R:" << f[EPlane::RIGHT]  << '\n';
    oss << "B:" << f[EPlane::BOTTOM] << '\n';
    oss << "T:" << f[EPlane::TOP]    << '\n';
    oss << "F:" << f[EPlane::FAR]    << '\n';
    oss << "N:" << f[EPlane::NEAR]   << '}';
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  inline std::ostream& operator <<(std::ostream& out, const CFrustum& f) {
    out << "f{" << '\n';
    out << "L:" << f[EPlane::LEFT]   << '\n';
    out << "R:" << f[EPlane::RIGHT]  << '\n';
    out << "B:" << f[EPlane::BOTTOM] << '\n';
    out << "T:" << f[EPlane::TOP]    << '\n';
    out << "F:" << f[EPlane::FAR]    << '\n';
    out << "N:" << f[EPlane::NEAR]   << '}';
    return out;
  }
  
  inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const sys::array<glm::plane,6>& planes) {
    std::ostringstream oss;
    oss << "p[6]{" << '\n';
    oss << "L:" << planes[EPlane::LEFT]   << '\n';
    oss << "R:" << planes[EPlane::RIGHT]  << '\n';
    oss << "B:" << planes[EPlane::BOTTOM] << '\n';
    oss << "T:" << planes[EPlane::TOP]    << '\n';
    oss << "F:" << planes[EPlane::FAR]    << '\n';
    oss << "N:" << planes[EPlane::NEAR]   << '}';
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  inline std::ostream& operator <<(std::ostream& out, const sys::array<glm::plane,6>& planes) {
    out << "p[6]{" << '\n';
    out << "L:" << planes[EPlane::LEFT]   << '\n';
    out << "R:" << planes[EPlane::RIGHT]  << '\n';
    out << "B:" << planes[EPlane::BOTTOM] << '\n';
    out << "T:" << planes[EPlane::TOP]    << '\n';
    out << "F:" << planes[EPlane::FAR]    << '\n';
    out << "N:" << planes[EPlane::NEAR]   << '}';
    return out;
  }
  
  inline const sys::CLogger::ELevel& operator <<(const sys::CLogger::ELevel& type, const sys::array<glm::vec3,8>& corners) {
    std::ostringstream oss;
    oss << "c[8]{" << '\n';
    oss << "LBN:" << corners[glm::ECorner::LBN] << '\n';
    oss << "RBN:" << corners[glm::ECorner::RBN] << '\n';
    oss << "LTN:" << corners[glm::ECorner::LTN] << '\n';
    oss << "RTN:" << corners[glm::ECorner::RTN] << '\n';
    oss << "LBF:" << corners[glm::ECorner::LBF] << '\n';
    oss << "RBF:" << corners[glm::ECorner::RBF] << '\n';
    oss << "LTF:" << corners[glm::ECorner::LTF] << '\n';
    oss << "RTF:" << corners[glm::ECorner::RTF] << '}';
    sys::CLogger::getSingleton()->push(oss.str());
    return type;
  }  
  
  inline std::ostream& operator <<(std::ostream& out, const sys::array<glm::vec3,8>& corners) {
    out << "c[8]{" << '\n';
    out << "LBN:" << corners[glm::ECorner::LBN] << '\n';
    out << "RBN:" << corners[glm::ECorner::RBN] << '\n';
    out << "LTN:" << corners[glm::ECorner::LTN] << '\n';
    out << "RTN:" << corners[glm::ECorner::RTN] << '\n';
    out << "LBF:" << corners[glm::ECorner::LBF] << '\n';
    out << "RBF:" << corners[glm::ECorner::RBF] << '\n';
    out << "LTF:" << corners[glm::ECorner::LTF] << '\n';
    out << "RTF:" << corners[glm::ECorner::RTF] << '}';
    return out;
  }
}

#endif //__glm_cfrustum_hpp__
