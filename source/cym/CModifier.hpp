#ifndef __cym_cmodifier_hpp__
#define __cym_cmodifier_hpp__

#include "cym/cym.hpp"

#include <vector>

namespace cym {
  using PModifier = sys::ptr<CModifier>;

  class CModifier {
    public:
      CModifier() = default;
      virtual ~CModifier() = default;
    public:
      virtual void onTick(float fDelta) { }
  };
  
  template <typename T> class TModifier : public CModifier {
    // ?
  };
} // namespace cym


#endif //__cym_cmodifier_hpp__