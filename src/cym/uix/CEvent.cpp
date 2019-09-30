#include "cym/uix/CEvent.hpp"

namespace cym::uix {
  CEvent::CEvent(const EEvent& type, CWindow* target) : mType{type}, mTarget{target} { }
  
  CEvent::~CEvent() { }
  
  std::ostream& operator <<(std::ostream& o, const CEvent& e) {
    return o << "CEvent: x=" << e.mClientX << " y=" << e.mClientY << " m=" << (int)(e.mModifier) << " k=" << e.mKey << " t=" << e.mTarget;
  }
}
