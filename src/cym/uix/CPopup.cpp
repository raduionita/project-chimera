#include "cym/uix/CPopup.hpp"

namespace cym { namespace uix {
  bool CPopup::fullscreen(uint nHints/*=7*/) {
    log::nfo << "uix::CWindow::fullscreen(int)::" << this << log::end;
    // @todo: chromium/window-style fullscreen
    
    // @todo: GET current state
    
    // @todo: IF hint == state THEN return
    
    // @todo: temp state = curr state
    
    // @todo: IF hint == fullscreen THEN: 
      // @todo: curr state = fullscreen (style & xy & wh)
    // @todo: IF hint == windowed THEN:
      // @todo: GET style & xy & wh &  from prev state
      // @todo: curr state = windowed (style & xy & wh)
      
    // @todo: prev state = temp state
    
    
    // @todo: on (app) exit/quit revert
    
    
    if (nHints & EFullscreen::FULLSCREEN) {
      // @todo: GWL_STYLE   remove ~(WS_CAPTION | WS_THICKFRAME)
      // @todo: GWL_EXSTYLE remove ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE)
    
      ::SetWindowLong(mHandle, GWL_STYLE, WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
      ::SetWindowLong(mHandle, GWL_EXSTYLE, 0);
      MONITORINFO sMI;
      sMI.cbSize = sizeof(sMI);
      ::GetMonitorInfo(::MonitorFromWindow(mHandle,MONITOR_DEFAULTTONEAREST), &sMI);
      return TRUE == ::SetWindowPos(mHandle, HWND_TOPMOST, sMI.rcMonitor.left, sMI.rcMonitor.top, sMI.rcMonitor.right-sMI.rcMonitor.left, sMI.rcMonitor.bottom-sMI.rcMonitor.top, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOACTIVATE);
    } else {
      // @todo: restore styles
      // @todo: restore rect (shape & position)
      
      ::SetWindowLong(mHandle, GWL_STYLE,   0); // restore dwStyle
      ::SetWindowLong(mHandle, GWL_EXSTYLE, 0); // restore dwExStyle
      return TRUE == ::SetWindowPos(mHandle, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOACTIVATE); // restore xywh
    
      // @todo: IF maxmized THEN:
      // ::ShowWindow(mHandle, SW_MAXIMIZE)
    }
    
    // @todo: remember:
      // dwStyle   // or hints
      // dwExStyle // but we need a method to convert from hints to DWORD style/exStyle
      // x, y
      // width, height
    
    return false;
  }
}}
