#include "cym/uix/CHandler.hpp"

namespace cym { namespace uix {
  CHandler::CHandler() {
    log::nfo << "uix::CHandler::CHandler()::" << this << log::end;
  }
  
  CHandler::~CHandler() {
    log::nfo << "uix::CHandler::~CHandler()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CHandler::detach(CHandler* pTarget, const EEvent& eEvent) {
    log::nfo << "uix::CHandler::detach(CHandler*, EEvent&)::" << this << log::end;
    // find callbacks for this event type
    auto it = pTarget->mCallbacks.find(eEvent);
    // if no callbacks: do nothing // else: erase
    if (it == pTarget->mCallbacks.end()) {
      // do nothing
      return false;
    } else {
      pTarget->mCallbacks.erase(it);  
      return true;
    }
  }
  
  bool CHandler::handle(CEvent* pEvent) {
    log::nfo << "app::CHandler::handle(CEvent*)::" << this << log::end;
    // here this = target (@see CWindow::proc)
    EEvent eEvent     =  pEvent->type();
    // get all callbacks for this event
    auto   aCallbacks =& mCallbacks[eEvent];
    // has handlers => will trigger
    bool   bTriggered =  aCallbacks->size() != 0;
    // only if it's triggerable
    if (bTriggered) for (auto it = aCallbacks->begin(); it != aCallbacks->end(); ++it) {
      // this will trigger the fCallback from CHandler::attach
      (*it)(pEvent);
    }
    // remove (old) pre-queued events // latest rulz
    auto it = mPrequeued.find(eEvent);
    if (it != mPrequeued.end()) {
      DELETE(it->second);
      mPrequeued.erase(it);
    }
    // if no handlers (attached) yet, pre-queue it
    if (!bTriggered) mPrequeued[eEvent] = pEvent;
    // return trigger status
    return bTriggered;
  }
}}
