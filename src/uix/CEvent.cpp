#include "uix/CEvent.hpp"

namespace uix {
  CEvent::CEvent(const EType& type, CWindow* target) : mType{type}, mTarget{target} { }
  
  CEvent::~CEvent() { }
  
  std::ostream& operator <<(std::ostream& o, const CEvent& e) {
    return o << "CEvent: x=" << e.mClientX << " y=" << e.mClientY << "w=" << e.mWidth << " h=" << e.mHeight << " m=" << (int)(e.mModifier) << " k=" << e.mKey << " t=" << e.mTarget;
  }
}
