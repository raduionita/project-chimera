#ifndef __uix_cwindow_hpp__
#define __uix_cwindow_hpp__

#include "uix/CObject.hpp"

namespace uix {
  class CWindow : public CObject {
      friend class CFrame;
      friend class CConsole;
    public:
      enum EState : int {
        EMPTY      = ZERO,
        INITED     = 1 <<  1,
        PUSHED     = 1 <<  2,
        RELEASED   = 1 <<  3,
        FOCUSED    = 1 <<  4,
        BLURRED    = 1 <<  5,
        CHECKED    = 1 <<  6,
        MINIMIZED  = 1 <<  7,
        MAXIMIZED  = 1 <<  8,
        FULLSCREEN = 1 <<  9,
        PAINTING   = 1 << 10, 
        CLICKED    = 1 << 11, 
        DBLCLICKED = 1 << 12, 
        DISABLED   = 1 << 13, 
        FREED      = 1 << 14,
      };
    protected:
      int mState {0};
    private:
      CWindow() = default;
    public:
      ~CWindow();
    protected:
      virtual bool init();
      virtual bool free();
  };
} // namespace uix

#endif //__uix_cwindow_hpp__