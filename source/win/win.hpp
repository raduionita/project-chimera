#ifndef __win_hpp__
#define __win_hpp__

#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>

namespace win {
  template<typename T> class TApplication;
  class CApplication;

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
} // namespace win


#endif //__win_hpp__