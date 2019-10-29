#ifndef __glm_hpp__
#define __glm_hpp__

#include <cmath>

namespace glm {
#ifdef GLM_DOUBLE_PRECISION
  typedef double real;
#else
  typedef float real;
#endif
  
  template <typename T> struct SRange {
    T min;
    T max;
  };
  
  template <typename T> void swap(T& lhs, T& rhs) { T tmp = lhs; lhs = rhs; rhs = tmp; }
  
  inline real loop(real& fVal, real fStep = 0.1f, real fFirst = -1.0f, real fLast = 1.0f) {
    bool bRevRange = fLast < fFirst;
    bool bRevStep  = fStep < 0.0f;
    int dir = 1;
    bRevRange && (dir *= -1);
    bRevStep  && (dir *= -1);
    // @todo: fix this for reverse cases
      // loop(val,-0.1f, -1.0f,+1.0f)
      // loop(val,-0.1f, +1.0f,-1.0f)
      // loop(val, 0.1f, +1.0f,-1.0f)
    fVal = fVal + dir * fStep;
    fVal = fVal > fLast ? fFirst : fVal;
    return fVal;
  }
  
  template <typename T> inline T log2(T value) { return static_cast<T>(std::log2(value)); }
  
  template <typename T> inline T floor(T value) { return static_cast<T>(std::floor(value)); }
  
  template <typename T> inline T min(T a, T b) { return a < b ? a : b; }
  
  template <typename T> inline T max(T a, T b) { return a >= b ? a : b; }
}

#endif //__glm_hpp__
