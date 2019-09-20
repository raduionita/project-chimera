#include "cym/uix/CEvent.hpp"

namespace cym { namespace uix {
  CEvent::CEvent(const EEvent& type, CListener* target) : mType{type}, mTarget{target} { }
  
  CEvent::~CEvent() {
    log::nfo << "uix::CEvent::~CEvent()::" << this << log::end;
  }
  
  std::ostream& operator <<(std::ostream& o, const CEvent& e) {
    return o << "CEvent: x=" << e.mClientX << " y=" << e.mClientY << " m=" << (int)(e.mModifier) << " k=" << e.mKey << " t=" << e.mTarget;
  }
}}
