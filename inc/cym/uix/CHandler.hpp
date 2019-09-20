#ifndef __cym_uix_chandler_hpp__
#define __cym_uix_chandler_hpp__

#include "uix.hpp"
#include "CEvent.hpp"

#include <functional>

namespace cym { namespace uix {
  class CHandler {
    private:
      std::map<EEvent, std::vector<std::function<void(CEvent*)>>> mCallbacks;
      std::map<EEvent, CEvent*>                                   mPrequeued;
    public:
      CHandler();
      virtual ~CHandler();
    protected:
      // @todo: template <typename L> bool attach(CHandler* pTarget, const EEvent& eEvent, L&& callback);
      template <typename T> bool attach(CHandler* pTarget, const EEvent& eEvent, void(T::*callback)(CEvent*)) {
        log::nfo << "uix::CHandler::attach(CHandler*, EEvent, void(T::*callback)(CEvent*))::" << this << log::end;
        // eg: T = CApplication & E = CKeyEvent
        
        // pointer to vector inside map
        auto aCallbacks =& pTarget->mCallbacks[eEvent]; 
        
        // wrap callback to a cast(ed) callback
        auto fCallback  = [this,callback] (CEvent* pEvent) {
          T* pHandler = dynamic_cast<T*>(this);
          (pHandler->*callback)(pEvent);
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
}}

#endif //__cym_uix_chandler_hpp__
