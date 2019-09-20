#ifndef __cym_uix_cevent_hpp__
#define __cym_uix_cevent_hpp__

#include "uix.hpp"

namespace cym { namespace uix {
  class CEvent {
      friend std::ostream& operator <<(std::ostream&, const CEvent&);
      friend class CWindow;
    protected:
      bool       mPropagate {true};
      EEvent     mType      {EEvent::EMPTY};
      CListener* mTarget    {nullptr};
      char       mKey       {'\0'};
      int        mClientX   {0};
      int        mClientY   {0};
      int        mModifier  {ZERO};
      EMouse     mButton    {EMouse::EMPTY};
      int        mWidth     {0};
      int        mHeight    {0};
      EState     mState     {EState::EMPTY};
    public:
      CEvent(const EEvent& type, CListener* target = nullptr);
      virtual ~CEvent();
    protected:
      inline void      type(const EEvent& eType)  { mType = eType; }
      inline void      key(char cKey)             { mKey = cKey;  }
      inline void      modifier(int nModifier)    { mModifier = nModifier; }
    public:
      inline EEvent    type() const               { return mType; }
      inline bool      propagate() const          { return mPropagate; }
      inline void      propagate(bool bPropagate) { mPropagate = bPropagate; }
      inline char      key() const                { return mKey; }
      inline int       modifier() const           { return mModifier; }
      inline int       width()  const             { return mWidth;  }
      inline int       height() const             { return mHeight; }
      inline EState    state()  const             { return mState;  }
      inline EMouse    button() const             { return mButton; }
      inline int       clientX() const            { return mClientX; }
      inline int       clientY() const            { return mClientY; }
  };
}}

#endif //__cym_uix_cevent_hpp__
