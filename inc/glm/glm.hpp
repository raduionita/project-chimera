#ifndef __glm_hpp__
#define __glm_hpp__

#include <cmath>

namespace glm {
  template <typename T> struct SRange {
    T min;
    T max;
  };
  
  template <typename T> void swap(T& lhs, T& rhs) {
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
  }
  
  inline float loop(float& fVal, float fStep = 0.1f, float fFirst = -1.0f, float fLast = 1.0f) {
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
}

#endif //__glm_hpp__
