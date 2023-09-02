#ifndef __uix_hpp__
#define __uix_hpp__

#include "sys/sys.hpp"

#ifdef PLATFORM_WINDOWS

#define uix32_LEAN_AND_MEAN // before <uixdows.h> exclude unusable stuff
#include <windows.h>

namespace uix {
  constexpr int ZERO =  0;

  class CObject;
    class CWindow;
      class CWidget;
        class CSurface;
        class CControl;
          class CButton;
      class CFrame;
        class CCanvas;
      class CDialog;
      class CConsole;

  class CApplication;
  template<typename T> class TApplication;
} // namespace uix

#endif // PLATFORM_uixDOW

#endif //__uix_hpp__