#ifndef __cym_uix_chandler_hpp__
#define __cym_uix_chandler_hpp__

#include "uix.hpp"
#include "CEvent.hpp"

#include <functional>

namespace cym { namespace uix {
  class CListener {
      typedef void(*TCallback)(CEvent*);
      typedef std::function<void(CEvent*)> THandler;
    private:
      std::map<EEvent,THandler> mHandlers;
    public:
      CListener();
      virtual ~CListener();
    protected:
      // attach: lambda
      bool attach(CListener*, const EEvent&, TCallback&&);
      // attach: method // eg: T = CApplication
      template <typename T> bool attach(CListener* pTarget, const EEvent& eEvent, void(T::*fCallback)(CEvent*)) {
        log::nfo << "uix::CListener::attach(CListener*, EEvent&, void(T::*fCallback)(CEvent*))::" << this << " EVT:" << int(eEvent) << log::end;
        // wrap callback to a cast(ed) callback // add to list of calbacks
        pTarget->mHandlers.insert(std::move(std::pair(eEvent, [this,fCallback] (CEvent* pEvent) {
          T* pHandler = dynamic_cast<T*>(this);
          (pHandler->*fCallback)(pEvent);
        }))); 
        return true;
      }
      // detach
      bool detach(CListener*, const EEvent&);
    public:
      bool handle(CEvent*);
      bool listens(const EEvent&) const;
  };
  
  class COnKeydownListener : public CListener {
    public:
      COnKeydownListener() { attach(this, EEvent::KEYDOWN, &COnKeydownListener::onKeydown); }
    public:
      virtual void onKeydown(CEvent*) = 0;
  };
  
  class COnClickListener : public CListener {
    public:
      COnClickListener() { attach(this, EEvent::CLICK, &COnClickListener::onClick); }
    public:
      virtual void onClick(CEvent*) = 0;
  };
}}

#endif //__cym_uix_chandler_hpp__
