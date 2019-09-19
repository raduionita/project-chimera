#include "cym/uix/CCanvas.hpp"
#include "cym/uix/CContext.hpp"

namespace cym { namespace uix {
  CCanvas::CCanvas(int nHints/*=ZERO*/) {
    log::nfo << "uix::CCanvas::CCanvas(int)::" << this << log::end;
    init(nullptr, {}, nHints | CCanvas::STYLE);
  }
  
  CCanvas::CCanvas(const SConfig& sConfig, int nHints/*=ZERO*/) {
    log::nfo << "uix::CCanvas::CCanvas(SConfig&,int)::" << this << log::end;
    init(nullptr, sConfig, nHints | CCanvas::STYLE);
  }
  
  CCanvas::CCanvas(CWindow* pParent, const SConfig& sConfig/*={}*/, int nHints/*=EHint::FRAME*/) {
    log::nfo << "uix::CCanvas::CCanvas(CWindow*,SConfig&,int)::" << this << log::end;
    init(pParent, sConfig, nHints | CCanvas::STYLE);
  }
  
  CCanvas::~CCanvas() {
    log::nfo << "uix::CCanvas::~CCanvas()::" << this << log::end;
    DELETE(mContext);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCanvas::init(CWindow* pParent, const SConfig& sConfig, int nHints) {
    log::nfo << "uix::CCanvas::init(CWindow*,SConfig&,int)::" << this << log::end;
  
    mInited = super::init(pParent, nHints);
    
    mInited && (mContext = new CContext(this, sConfig));
    
    return mInited;
  }
  
  bool CCanvas::fullscreen(uint nHints/*=3*/) {
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
    
    // @todo: GWL_STYLE   remove ~(WS_CAPTION | WS_THICKFRAME)
    // @todo: GWL_EXSTYLE remove ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE)

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
      sDM.dmFields     = DM_PELSWIDTH | DM_PELSHEIGHT;
      
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
  
  bool CCanvas::swap()    const       { return mContext->swap(); }
  bool CCanvas::current() const       { return mContext->current(); }
  bool CCanvas::clear(int nBit) const { return mContext->clear(nBit); }
  bool CCanvas::reset() const         { return mContext->reset(); }
}}
