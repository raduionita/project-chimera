#include "uix/CListener.hpp"

namespace uix {
  CListener::CListener() {
    CYM_LOG_NFO("uix::CListener::CListener()::" << this);
  }
  
  CListener::~CListener() {
    CYM_LOG_NFO("uix::CListener::~CListener()::" << this);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CListener::attach(CListener* pTarget, const CEvent::EType& eEvent, FCallback&& fCallback) {
    CYM_LOG_NFO("uix::CListener::attach(CListener*, EType&, TCallback&&)::" << this);
    // add to list of calbacks
    pTarget->mHandlers[eEvent] = fCallback; 
    // done
    return true;
  }
  
  bool CListener::detach(CListener* pTarget, const CEvent::EType& eEvent) {
    CYM_LOG_NFO("uix::CListener::detach(CListener*, EType&)::" << this);
    // find callbacks for this event type
    auto it = pTarget->mHandlers.find(eEvent);
    if (it != pTarget->mHandlers.end()) {
      pTarget->mHandlers.erase(it);
      return true;
    }
    return false;
  }
  
  bool CListener::handle(CEvent* pEvent) {
    CYM_LOG_NFO("app::CListener::handle(CEvent*)::" << this << " EVENT:" << (int)(pEvent->type()));
    
    if (mHandlers.count(pEvent->type()) > 0) {
      mHandlers[pEvent->type()](pEvent);
      return true;
    }
    return false;
  }
  
  bool CListener::listens(const CEvent::EType& eEvent) const { 
    CYM_LOG_NFO("uix::CListener::listens(CEvent::EType&)::" << this << " EVT:" << int(eEvent) << " " << mHandlers.count(eEvent));
    return mHandlers.count(eEvent) > 0; 
  }
}
