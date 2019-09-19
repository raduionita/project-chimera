#include "cym/uix/CPopup.hpp"

namespace cym { namespace uix {
  bool CPopup::fullscreen(uint nHints/*=7*/) {
    log::nfo << "uix::CPopup::fullscreen(int)::" << this << log::end;
    
    // @todo: on (app) exit/quit revert
    
    if (nHints & EFullscreen::FULLSCREEN) {
      // if cur state = new state: do nothing
      if (mState & EState::FULLSCREEN) return false;
      // swap curr state w/ old state // return curr state
      STATE sState = ::SwapWindowState(mHandle);
      // set new styles
      ::SetWindowLong(mHandle, GWL_STYLE,   sState.dwStyle & ~(WS_CAPTION | WS_THICKFRAME));
      ::SetWindowLong(mHandle, GWL_EXSTYLE, sState.dwExStyle & ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));
      MONITORINFO sMI;
      sMI.cbSize = sizeof(sMI);
      ::GetMonitorInfo(::MonitorFromWindow(mHandle,MONITOR_DEFAULTTONEAREST), &sMI);
      // set new xywh
      ::SetWindowPos(mHandle, HWND_TOPMOST, sMI.rcMonitor.left, sMI.rcMonitor.top, sMI.rcMonitor.right-sMI.rcMonitor.left, sMI.rcMonitor.bottom-sMI.rcMonitor.top, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOACTIVATE);
      // send fullscreen message
      ::SendMessage(mHandle, CM_FULLSCREEN, 0, 0/*,WPARAM wParam,LPARAM lParam*/);
    } else {
      // if cur state = new state: do nothing
      if (!(mState & EState::FULLSCREEN)) return false;
      // swap curr state w/ old state // return prev state
      STATE sState = ::SwapWindowState(mHandle);
      // restore styles
      ::SetWindowLong(mHandle, GWL_STYLE,   sState.dwStyle); // restore dwStyle
      ::SetWindowLong(mHandle, GWL_EXSTYLE, sState.dwExStyle); // restore dwExStyle
      ::SetWindowPos(mHandle, NULL, sState.rc.left, sState.rc.top, sState.rc.right-sState.rc.left, sState.rc.bottom-sState.rc.top, SWP_FRAMECHANGED|SWP_NOZORDER|SWP_NOACTIVATE); // restore xywh
      // send windowed message
      ::SendMessage(mHandle, CM_WINDOWED, 0, 0/*,WPARAM wParam,LPARAM lParam*/);
      
      // @todo: IF maxmized THEN:
      // ::ShowWindow(mHandle, SW_MAXIMIZE) 
    }
    return true;
  }
}}
