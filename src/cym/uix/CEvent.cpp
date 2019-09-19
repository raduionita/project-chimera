#include "cym/uix/CEvent.hpp"

namespace cym { namespace uix {
  CEvent::CEvent(EEvent type, CHandler* target/*=nullptr*/) : mType{type}, mTarget{target} { }
  
  CCloseEvent::CCloseEvent(CHandler* pTarget) : CEvent(EEvent::CLOSE, pTarget) {}
  
  CMouseEvent::CMouseEvent(EEvent type/*=EEvent::CLICK*/, CHandler* target/*=nullptr*/) : CEvent(type, target) {}
  
  CResizeEvent::CResizeEvent(CHandler* pHandler) : CEvent(EEvent::RESIZE, pHandler) { mPropagate = false; }
  
  CKeyEvent::CKeyEvent(EEvent type/*=EEvent::KEYDOWN*/, CHandler* target/*=nullptr*/) : CEvent(type, target) {}
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  std::ostream& operator <<(std::ostream& o, const CMouseEvent& e) {
    return o << "CMouseEvent: x=" << e.mClientX << " y=" << e.mClientY << " m=" << (int)(e.mModifier) << " c=" << e.mClick << " t=" << e.mTarget;
  }
}}
