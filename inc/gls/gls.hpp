#ifndef __gls_hpp__
#define __gls_hpp__

#include "glc/glc.hpp"

namespace gls {
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
  class CRay;
  class CCircle;
  class CEllipse;
  class CArc;
  class CSpline;
  class CSector;
  class CPolygon;
  class CRectangle;
  class CPlane;
  class CTriangle; // extends poly
  
  class CPrism;
  class CPyramid;
  class CCube;
  class CSphere;
  
  class CTesseract; // hypercube = 4(spacial)d  cube
}

#endif //__gls_hpp__
