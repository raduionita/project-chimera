#include "cym/uix/CCanvas.hpp"
#include "cym/uix/CContext.hpp"

namespace cym::uix {
  CCanvas::CCanvas(int nHints/*=ZERO*/) {
    log::nfo << "uix::CCanvas::CCanvas(int)::" << this << log::end;
    init(nullptr, {}, nHints | CCanvas::WINDOW);
  }
  
  CCanvas::CCanvas(const CContext::SConfig& sConfig, int nHints/*=ZERO*/) {
    log::nfo << "uix::CCanvas::CCanvas(CContext::SConfig&,int)::" << this << log::end;
    init(nullptr, sConfig, nHints | CCanvas::WINDOW);
  }
  
  CCanvas::CCanvas(CWindow* pParent, const CContext::SConfig& sConfig/*={}*/, int nHints/*=EWindow::FRAME*/) {
    log::nfo << "uix::CCanvas::CCanvas(CWindow*,CContext::SConfig&,int)::" << this << log::end;
    init(pParent, sConfig, nHints | CCanvas::WINDOW);
  }
  
  CCanvas::~CCanvas() {
    log::nfo << "uix::CCanvas::~CCanvas()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCanvas::init(CWindow* pParent, const CContext::SConfig& sConfig, int nHints) {
    log::nfo << "uix::CCanvas::init(CWindow*,CContext::SConfig&,int)::" << this << log::end;
    return mInited = (CFrame::init(pParent, nHints) && CRender::init(this, sConfig));
  }
  
  bool CCanvas::fullscreen(uint nHints/*=1*/) {
    log::nfo << "uix::CCanvas::fullscreen(int)::" << this << log::end;
    // @todo: game-style fullscreen
    
    
    return super::fullscreen(nHints);
    
    int nWidth;
    int nHeight;
    
    // hint: 100b = 4 = use monitor rez
    if (nHints & EFullscreen::MONITOR) {
      nWidth  = ::GetSystemMetrics(SM_CXSCREEN);
      nHeight = ::GetSystemMetrics(SM_CYSCREEN);
    } else {
      RECT sRect;
      ::GetClientRect(mHandle, &sRect); // for remembering windows pos
      nWidth  = sRect.right - sRect.left;
      nHeight = sRect.bottom - sRect.top;
    }
    
    if (nHints & EFullscreen::FULLSCREEN) {
      // hint: 001b = 1 = fullscreen
      ::SetWindowLong(mHandle, GWL_EXSTYLE, 0);
      ::SetWindowLong(mHandle, GWL_STYLE,   WS_POPUP|WS_CLIPCHILDREN|WS_CLIPSIBLINGS);
      
      ::SetWindowPos(mHandle, HWND_TOPMOST, 0,0,0,0, SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED|SWP_SHOWWINDOW);
      ::SetWindowPos(mHandle, HWND_TOPMOST, 0,0,nWidth,nHeight, SWP_SHOWWINDOW);
      
      // @todo:   010b = 2 = w/ cursor
      ::ShowCursor(FALSE);
      
      DEVMODE sDM;
      sDM.dmSize       = sizeof(DEVMODE);
      sDM.dmPelsWidth  = nWidth;
      sDM.dmPelsHeight = nHeight;
      sDM.dmBitsPerPel = 24;
      sDM.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
      
      // ::EnumDisplayDevices
      // ::EnumDisplaySettings
      
      // ::GetSystemMetrics(SM_CXSCREEN) // width px  // primary monitor
      // ::GetSystemMetrics(SM_CYSCREEN) // height px // primary monitor
      
      // ::GetDeviceCaps 
    
      // ::SystemParametersInfo // working area w/o taskbar
      
      // MONITORINFO sMI;
      // ::MonitorFromWindow(mHandle, MONITOR_DEFAULTTONEAREST);
      // ::GetMonitorInfo // specific monitor
      
      return ::ChangeDisplaySettings(&sDM,0) == DISP_CHANGE_SUCCESSFUL;
    } else {
      // hint: 000b = 0 = windowed    // center of windowed
      
    }
  }
}
