#ifndef __cym_uix_clistener_hpp__
#define __cym_uix_clistener_hpp__

#include "CEvent.hpp"

#include <map>
#include <functional>
#include <vector>

namespace cym { namespace uix {
  class CListener {
    private:
      std::map<EEvent, std::vector<std::function<void(CEvent*)>>> mCallbacks;
      std::map<EEvent, CEvent*>                                   mPrequeued;
    public:
      CListener() = default;
      virtual ~CListener() = default;
    protected:
      template <typename T, typename E> bool attach(CListener* pTarget, const EEvent& eEvent, void(T::*callback)(E*)) {
        log::nfo << "uix::CListener::attach(CListener*, EEvent, void(T::*callback)(CEvent*))::" << this << log::end;
        // eg: T = CApplication & E = CKeyEvent
      
        // pointer to vector inside map
        auto aCallbacks =& pTarget->mCallbacks[eEvent];
      
        // wrap callback to a cast(ed) callback
        auto fCallback  = [this,callback] (CEvent* pEvent) {
          T* pHandler = dynamic_cast<T*>(this);
          E* pCasted  = dynamic_cast<E*>(pEvent);
          (pHandler->*callback)(pCasted);
        };
      
        // if has queued (already triggered)
        auto it = mPrequeued.find(eEvent);
        // pre-trigger the previously enqueued event
        if(it != mPrequeued.end()) { fCallback(it->second); }
      
        // add to list of calbacks
        aCallbacks->push_back(std::move(fCallback));
      
        return true;
      }
      bool detach(CHandler*, const EEvent&);
    public:
      bool handle(CEvent*);
  };
  
  class COnKeydownListener : public CListener {
    public:
      COnKeydownListener() { attach(this, EEvent::KEYDOWN, &COnKeydownListener::onKeydown); }
    public:
      virtual void onKeydown(CKeyEvent*) = 0;
  };
  
  class COnClickListener : public CListener {
    public:
      COnClickListener() { attach(this, EEvent::CLICK, &COnClickListener::onClick); }
    public:
      virtual void onClick(CMouseEvent*) = 0;
  };
}}

#endif //__cym_uix_clistener_hpp__
