#ifndef __uix_cevent_hpp__
#define __uix_cevent_hpp__

#include "uix/uix.hpp"

namespace uix {
  class CEvent {
      friend std::ostream& operator <<(std::ostream&, const CEvent&);
      friend class CWindow;
      friend class CButton;
    public:
      enum EType {
        // 0b00000000'00000000'00000000'00000000
        EVENT       = 0,
          WINDOW    = 1, // << 0
        INIT        = 1 <<  1 | WINDOW,
        CLOSE       = 1 <<  2 | WINDOW,
        QUIT        = 1 <<  3 | WINDOW,
        PAINT       = 1 <<  4 | WINDOW, DRAW = PAINT,
        SHOW        = 1 <<  5 | WINDOW,
        HIDE        = 1 <<  6 | WINDOW,
        MOVE        = 1 <<  7 | WINDOW,
        MOVING      = 1 <<  8 | WINDOW,
        RESIZE      = 1 <<  9 | WINDOW, SIZE = RESIZE,
        SIZING      = 1 << 10 | WINDOW,
        FOCUS       = 1 << 11 | WINDOW,
        UNFOCUS     = 1 << 12 | WINDOW, BLUR = UNFOCUS,
        COMMAND     = 1 << 13 | WINDOW,
          INPUT     = 1 << 14,
          KEYBOARD  = 1 << 15 | INPUT,
        KEYDOWN     = 1 << 16 | KEYBOARD,
        KEYUP       = 1 << 17 | KEYBOARD,
        KEYPRESSED  = KEYDOWN, // @todo: KEYDOWN | KEYUP,
          MOUSE     = 1 << 18 | INPUT,
        MOUSEMOVE   = 1 << 19 | MOUSE, 
        LBDOWN      = 1 << 20 | MOUSE, 
        LBUTTONDOWN = LBDOWN,
        LBUP        = 1 << 21 | MOUSE,
        LBUTTONUP   = LBUP,
        CLICK       = LBDOWN, // @todo: LBDOWN | LBUP
        LCLICK      = LBDOWN,
        RBDOWN      = 1 << 22 | MOUSE, 
        RBUTTONDOWN = RBDOWN,
        RBUP        = 1 << 23 | MOUSE, 
        RBUTTONUP   = RBUP,
        RCLICK      = RBDOWN, // @todo: RBDOWN | RBUP
        DBLCLICK    = 1 << 24 | MOUSE,
        DCLICK      = DBLCLICK,
      };
    protected:
      bool       mPropagate {bool(UIX_EVENT_PROPAGATE)};
      EType      mType      {EType::EVENT};
      CWindow*   mTarget    {nullptr};
      CControl*  mControl   {nullptr};
      char       mKey       {'\0'};
      int        mClientX   {0};
      int        mClientY   {0};
      EMouse     mModifier  {EMouse::EMPTY};
      EMouse     mButton    {EMouse::EMPTY};
      int        mWidth     {0};
      int        mHeight    {0};
      EState     mState     {EState::EMPTY};
    public:
      CEvent(const EType& type, CWindow* target = nullptr);
      virtual ~CEvent();
    public:
      friend int  operator  &(CEvent::EType lhs, CEvent::EType rhs);
      friend int  operator  &(int           lhs, CEvent::EType rhs);
      friend int  operator  |(CEvent::EType lhs, CEvent::EType rhs);
      friend int  operator  |(int           lhs, CEvent::EType rhs);
      friend int  operator  ~(CEvent::EType rhs);
      inline bool operator ==(const EType& eType) const { return static_cast<uint>(mType) & static_cast<uint>(eType); }
      inline uint operator  &(const EType& eType) const { return mType & eType; }
    protected:
      inline void      type(const EType& eType)   { mType = eType; }
      inline void      key(char cKey)             { mKey = cKey;  }
      inline void      modifier(uint nModifier)    { nModifier = static_cast<uint>(mModifier); }
    public:
      inline void      propagate(bool bPropagate) { mPropagate = bPropagate; }
      inline bool      propagate() const          { return mPropagate; }
      inline EType     type() const               { return mType; }
      inline CWindow*  target() const             { return mTarget; }
      inline CControl* control() const            { return mControl; }
      inline char      key() const                { return mKey; }
      inline EMouse    modifier() const           { return mModifier; }
      inline int       width()  const             { return mWidth;  }
      inline int       height() const             { return mHeight; }
      inline EState    state()  const             { return mState;  }
      inline EMouse    button() const             { return mButton; }
      inline int       clientX() const            { return mClientX; }
      inline int       clientY() const            { return mClientY; }
  };
  
  inline int operator &(CEvent::EType lhs, CEvent::EType rhs) { return static_cast<int>(lhs) & static_cast<uint>(rhs); }
  inline int operator &(int           lhs, CEvent::EType rhs) { return lhs                   & static_cast<uint>(rhs); }
  inline int operator |(CEvent::EType lhs, CEvent::EType rhs) { return static_cast<int>(lhs) | static_cast<int>(rhs); }
  inline int operator |(int           lhs, CEvent::EType rhs) { return lhs                   | static_cast<int>(rhs); }
  inline int operator ~(CEvent::EType rhs)                    { return ~(static_cast<int>(rhs)); }
  
  using EEvent = CEvent::EType;
}

#endif //__uix_cevent_hpp__
