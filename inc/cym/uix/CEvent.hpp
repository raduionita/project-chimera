#ifndef __cym_uix_cevent_hpp__
#define __cym_uix_cevent_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CEvent {
      friend class CWindow;
    protected:
      bool      mPropagate {true};
      EEvent    mType      {EEvent::_EVENT_};
      CHandler* mTarget    {nullptr};
    public:
      CEvent(EEvent type, CHandler* target = nullptr);
      virtual ~CEvent() = default;
    protected:
      inline void   type(const EEvent& type)  { mType = type; }
    public:
      inline EEvent type() const              { return mType; }
      inline bool   propagate() const         { return mPropagate; }
      inline void   propagate(bool propagate) { mPropagate = propagate; }
  };
  
  class CKeyEvent : public CEvent {
      friend class CWindow;
    protected:
      char mKey {'\0'};
    public:
      CKeyEvent(EEvent type = EEvent::KEYDOWN, CHandler* target = nullptr);
    protected:
      inline void key(char key) { mKey = key;  }
    public:
      inline char key() const   { return mKey; }
  };
  
  class CMouseEvent : public CEvent {
      using CEvent::CEvent;
      friend std::ostream& operator <<(std::ostream&, const CMouseEvent&);
    public:
      int       mClientX  {0};
      int       mClientY  {0};
      bool      mClick    {false};
      EModifier mModifier {EModifier::_MODIFIER_};
    public:
      CMouseEvent(EEvent type = EEvent::CLICK, CHandler* target = nullptr);
    protected:
      inline void click(bool bClick)                   { mClick = bClick; }
      inline void modifier(const EModifier& eModifier) { mModifier = eModifier; }
    public:
      inline bool      click() const    { return mClick; }
      inline EModifier modifier() const { return mModifier; }
  };
  
  class CCloseEvent : public CEvent {
      using CEvent::CEvent;
    public:
      CCloseEvent(CHandler* pTarget = nullptr);
  };
  
  class CResizeEvent : public CEvent {
      using CEvent::CEvent;
    public:
      int    mWidth  = {0};
      int    mHeight = {0};
      EState mState  = {EState::_STATE_};
    public:
      CResizeEvent(CHandler* pHandler = nullptr);
    public:
      inline int    width()  const { return mWidth;  }
      inline int    height() const { return mHeight; }
      inline EState state()  const { return mState;  }
  };
}}

#endif //__cym_uix_cevent_hpp__
