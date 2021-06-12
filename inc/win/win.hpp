#ifndef __win_hpp__
#define __win_hpp__

// @todo: move this to CWindow
#define WIN32_LEAN_AND_MEAN // before <windows.h> exclude unusable stuff
#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <wingdi.h>
#include <commctrl.h>

namespace win {
  class CWindow;
  
}

#endif //__win_hpp__
