#ifndef __cym_uix_cevent_hpp__
#define __cym_uix_cevent_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CEvent {
      friend std::ostream& operator <<(std::ostream&, const CEvent&);
      friend class CWindow;
    protected:
      bool      mPropagate {true};
      EEvent    mType      {EEvent::_EVENT_};
      CHandler* mTarget    {nullptr};
      char      mKey       {'\0'};
      int       mClientX   {0};
      int       mClientY   {0};
      EModifier mModifier  {EModifier::_MODIFIER_};
      int       mWidth     {0};
      int       mHeight    {0};
      EState    mState     {EState::_STATE_};
    public:
      CEvent(const EEvent& type, CHandler* target = nullptr);
      virtual ~CEvent() = default;
    protected:
      inline void      type(const EEvent& type)             { mType = type; }
      inline void      key(char key)                        { mKey = key;  }
      inline void      modifier(const EModifier& eModifier) { mModifier = eModifier; }
    public:
      inline EEvent    type() const              { return mType; }
      inline bool      propagate() const         { return mPropagate; }
      inline void      propagate(bool propagate) { mPropagate = propagate; }
      inline char      key() const               { return mKey; }
      inline EModifier modifier() const          { return mModifier; }
      inline int       width()  const            { return mWidth;  }
      inline int       height() const            { return mHeight; }
      inline EState    state()  const            { return mState;  }
  };
}}

#endif //__cym_uix_cevent_hpp__
