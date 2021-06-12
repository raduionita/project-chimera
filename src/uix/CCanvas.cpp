#include "uix/CCanvas.hpp"
#include "uix/CContext.hpp"

namespace uix {
  CCanvas::CCanvas(uint nHints) : mContext{new CContext{this}} {
    CYM_LOG_NFO("uix::CCanvas::CCanvas(CContext::SConfig&,uint)::" << this);
    CCanvas::init(nullptr,"",AUTO,nHints|WINDOW);
  }
  
  CCanvas::CCanvas(const CContext::SConfig& sConfig, uint nHints/*=WINDOW*/) : mContext{new CContext{this,sConfig}} {
    CYM_LOG_NFO("uix::CCanvas::CCanvas(CContext::SConfig&,uint)::" << this);
    CCanvas::init(nullptr,"",AUTO,nHints|WINDOW);
  }
  
  CCanvas::CCanvas(CWindow* pParent, const CContext::SConfig& sConfig/*={}*/, uint nHints/*=WINDOW*/) : mContext{new CContext{this,sConfig}} {
    CYM_LOG_NFO("uix::CCanvas::CCanvas(CWindow*,CContext::SConfig&,uint)::" << this);
    CCanvas::init(pParent,"",AUTO,nHints|WINDOW);
  }
  
  CCanvas::~CCanvas() {
    CYM_LOG_NFO("uix::CCanvas::~CCanvas()::" << this);
    // DELETE(mContext);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  bool CCanvas::init(CWindow* pParent/*=nullptr*/, const CString& tTitle/*=""*/, const SArea& tArea/*=AUTO*/, uint nHints/*=WINDOW*/) {
    CYM_LOG_NFO("uix::CCanvas::init(CWindow*,CContext::SConfig&,int)::" << this);
    
    RETURN((mState & EState::INITED),true);
    
    bool bInited = (CFrame::init(pParent,tTitle,tArea,nHints) && mContext->init(this));
    
    attach(this, uix::CEvent::EType::RESIZE,  &uix::CCanvas::onResize);
    
    return bInited;
  }
  
  bool CCanvas::fullscreen(uint nHints/*=1*/) {
    CYM_LOG_NFO("uix::CCanvas::fullscreen(int)::" << this);
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
  
  bool        CCanvas::current() const       { return mContext->current(); }
  bool        CCanvas::clear(int nBit) const { return mContext->clear(nBit); }
  bool        CCanvas::reset() const         { return mContext->reset(); }
  const char* CCanvas::version() const       { return mContext->version(); }
  
  void CCanvas::onResize(CEvent* pEvent) {
    CYM_LOG_NFO("uix::CCanvas::onResize(CEvent*)::" << this << " " << *pEvent);
    // update render viewport
    GLCALL(::glViewport(pEvent->clientX(),pEvent->clientY(),pEvent->width(),pEvent->height()));
  }
}
