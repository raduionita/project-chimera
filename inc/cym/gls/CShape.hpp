#ifndef __cym_gls_cshape_hpp__
#define __cym_gls_cshape_hpp__

namespace cym { namespace gls {
  // @note: matematical surface descriptors
  
  enum class EShape {
      S1D = 1,
      S2D = 2,
      S3D = 3,
      S4D = 4,
  };
  
  class CShape;
  class CPoint;
  class CLine;
  class CCircle;
  class CEllipse;
  class CArc;
  class CSpline;
  class CSector;
  class CPolygon;
  class CRectangle;
  class CTriangle; // extends poly
  
  class CSphere;
  class CPrism;
  class CPyramid;
  class CCube;
  
  
  
}

#endif //__cym_gls_cshape_hpp__
