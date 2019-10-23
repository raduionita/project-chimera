#include "uix/CListener.hpp"

namespace uix {
  CListener::CListener() {
    log::nfo << "uix::CListener::CListener()::" << this << log::end;
  }
  
  CListener::~CListener() {
    log::nfo << "uix::CListener::~CListener()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CListener::attach(CListener* pTarget, const EEvent& eEvent, TCallback&& fCallback) {
    log::nfo << "uix::CListener::attach(CListener*, EEvent&, TCallback&&)::" << this << log::end;
    // add to list of calbacks
    pTarget->mHandlers[eEvent] = fCallback; 
    // done
    return true;
  }
  
  bool CListener::detach(CListener* pTarget, const EEvent& eEvent) {
    log::nfo << "uix::CListener::detach(CListener*, EEvent&)::" << this << log::end;
    // find callbacks for this event type
    auto it = pTarget->mHandlers.find(eEvent);
    if (it != pTarget->mHandlers.end()) {
      pTarget->mHandlers.erase(it);
      return true;
    }
    return false;
  }
  
  bool CListener::handle(CEvent* pEvent) {
    log::nfo << "app::CListener::handle(CEvent*)::" << this << " EVENT:" << (int)(pEvent->type()) << log::end;
    if (mHandlers.count(pEvent->type()) > 0) {
      mHandlers[pEvent->type()](pEvent);
      return true;
    }
    return false;
  }
  
  bool CListener::listens(const EEvent& eEvent) const { 
    log::nfo << "uix::CListener::listens(EEvent&)::" << this << " EVT:" << int(eEvent) << " " << mHandlers.count(eEvent) << log::end;
    return mHandlers.count(eEvent) > 0; 
  }
}
