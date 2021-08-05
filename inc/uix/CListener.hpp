#ifndef __uix_chandler_hpp__
#define __uix_chandler_hpp__

#include "uix/uix.hpp"
#include "uix/CEvent.hpp"

#include <functional>

namespace uix {
  class CListener {
      typedef void(*FCallback)(CEvent*);
      typedef std::function<void(CEvent*)> FHandler;
    private:
      std::map<CEvent::EType,FHandler> mHandlers;
    public:
      CListener();
      virtual ~CListener();
    protected:
      // attach: lambda
      bool attach(CListener*, const CEvent::EType&, FCallback&&);
      // attach: method // eg: T = CApplication
      template<typename T> bool attach(CListener* pTarget, const CEvent::EType& eEvent, void(T::*fCallback)(CEvent*)) {
        CYM_LOG_NFO("uix::CListener::attach(CListener*,EType&,void(T::*fCallback)(CEvent*))::" << this << " E:" << int(eEvent));
        // wrap callback to a cast(ed) callback // add to list of calbacks
        pTarget->mHandlers[eEvent] = [that = dynamic_cast<T*>(this),fCallback] (CEvent* pEvent) {
          //T* pHandler = dynamic_cast<T*>(this);
          (that->*fCallback)(pEvent);
        }; 
        // replaces element
        return true;
      }
      // detach
      bool detach(CListener*, const CEvent::EType&);
    public:
      bool handle(CEvent*);
      bool listens(const CEvent::EType&) const;
  };
  
  class COnKeydownListener : public CListener {
    public:
      COnKeydownListener() { attach(this, CEvent::EType::KEYDOWN, &COnKeydownListener::onKeydown); }
    public:
      virtual void onKeydown(CEvent*) = 0;
  };
  
  class COnClickListener : public CListener {
    public:
      COnClickListener() { attach(this, CEvent::EType::CLICK, &COnClickListener::onClick); }
    public:
      virtual void onClick(CEvent*) = 0;
  };
  
  class COnResizeListener : public CListener {
    public:
      COnResizeListener() { attach(this, CEvent::EType::RESIZE, &COnResizeListener::onResize); }
    public:
      virtual void onResize(CEvent*) = 0;
  };
}

#endif //__uix_chandler_hpp__
