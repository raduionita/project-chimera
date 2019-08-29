#ifndef QUAT_HPP_INCLUDED
#define QUAT_HPP_INCLUDED

#include <ostream>
#include <cmath>

namespace dae 
{
  namespace math
  {
    
    // q = (x + yi + zj + wk)
    // i^2 = j^2 = k^2 = ikj = -1
    // i = jk
    // j = jk
    // k = ij
    
    // q1 = (x1 + y1i + z1j + w1k)
    // q2 = (x2 + y2i + z2j + w2k)
    // q1q2 = x1x2 - y1y2 - z1z2 - w1w2
    //      + (x1y2 + y1x2 + z1w2 - w1z2)i
    //      + (x1z2 - y1w2 + z1x2 + w1y2)j
    //      + (x1w2 + y1z2 - z1y2 + w1x2)k
    
    
    
    
    
  }
}
#endif // QUAT_HPP_INCLUDED