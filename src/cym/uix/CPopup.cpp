#include "cym/uix/CPopup.hpp"

namespace cym { namespace uix {
  bool CPopup::fullscreen(int nHints/*=7*/) {
    log::dbg << "uix::CWindow::fullscreen(int)::" << this << log::end;
    // @todo:   000b = 0 = windowed    // center of windowed
    // @todo:   001b = 1 = fullscreen
    // @todo:   010b = 2 = w/ cursor
    // @todo:   100b = 4 = use monitor rez
    
    RECT sRect;
    ::GetClientRect(mHandle, &sRect); // for remembering windows pos
    
    int nWidth  = sRect.right - sRect.left;
    int nHeight = sRect.bottom - sRect.top;
    
    ::SetWindowLong(mHandle, GWL_EXSTYLE, 0);
    ::SetWindowLong(mHandle, GWL_STYLE,   WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
    
    ::SetWindowPos(mHandle, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED|SWP_SHOWWINDOW);
    ::SetWindowPos(mHandle, HWND_TOPMOST, 0,0,nWidth,nHeight, SWP_SHOWWINDOW);
    
    ::ShowCursor(FALSE);
    
    DEVMODE sDM;
    sDM.dmSize       = sizeof(DEVMODE);
    sDM.dmPelsWidth  = nWidth;
    sDM.dmPelsHeight = nHeight;
    sDM.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
    
    // ::EnumDisplayDevices
    // ::EnumDisplaySettings
    
    // ::GetSystemMetrics(SM_CXSCREEN) // width px  // primary monitor
    // ::GetSystemMetrics(SM_CYSCREEN) // height px // primary monitor
    
    // ::GetDeviceCaps 
  
    // ::SystemParametersInfo // working area w/o taskbar
    
    // ::GetMonitorInfo // specific monitor
    
    return ::ChangeDisplaySettings(&sDM,0) == DISP_CHANGE_SUCCESSFUL;
  }
}}
