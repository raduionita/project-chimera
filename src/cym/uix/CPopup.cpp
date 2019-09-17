#include "cym/uix/CPopup.hpp"

namespace cym { namespace uix {
  bool CPopup::fullscreen(int nHints/*=3*/) {
    log::dbg << "uix::CWindow::fullscreen(int)::" << this << log::end;
    // @todo:    0b = 0 = windowed
    // @todo:   01b = 1 = fullscreen
    // @todo:   10b = 2 = w/ cursor
    
    RECT sRect;
    ::GetWindowRect(mHandle, &sRect); // for remembering windows pos
    
    ::SetWindowLong(mHandle, GWL_EXSTYLE, 0);
    ::SetWindowLong(mHandle, GWL_STYLE,   WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
    
    ::SetWindowPos(mHandle, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED|SWP_SHOWWINDOW);
    ::SetWindowPos(mHandle, HWND_TOPMOST, 0,0,800,600, SWP_SHOWWINDOW);
    
    ::ShowCursor(FALSE);
    
    DEVMODE sDM;
    sDM.dmSize       = sizeof(DEVMODE);
    sDM.dmPelsWidth  = 800;
    sDM.dmPelsHeight = 600;
    sDM.dmBitsPerPel = 24;
    sDM.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
  
    return ::ChangeDisplaySettings(&sDM,0) == DISP_CHANGE_SUCCESSFUL;
  }
}}
