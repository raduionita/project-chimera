#include "cym/uix/CApplication.hpp"
#include "cym/uix/CConsole.hpp"

namespace cym { namespace uix {
  CApplication* CApplication::sInstance{nullptr};
  
  CApplication::CApplication(HINSTANCE hHandle/*=::GetModuleHandle(NULL)*/, int nCmdShow/*=0*/) : CObject(), mHandle{hHandle} {
    log::nfo << "uix::CApplication::CApplication()::" << this << " INSTANCE:" << mHandle << log::end;
    assert(!sInstance && "CApplication::sIntastace already defined. Only one CApplication instance allowed!");
    mConsole  = new CConsole(this, nCmdShow);
    sInstance = this;
  }
  
  CApplication::~CApplication() {
    log::nfo << "uix::CApplication::~CApplication()::" << this << log::end;
  }
  
  CApplication::CApplication(const CApplication&) {
    log::nfo << "uix::CApplication::CApplication(CApplication&)::" << this << log::end;
  }
  
  CApplication& CApplication::operator =(const CApplication& that) {
    if (this != &that) {
      
    }
    return *this;
  }
  
  CApplication::operator HINSTANCE() {
    return mHandle;
  }
  
  CApplication::operator const HINSTANCE() const {
    return mHandle;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  bool CApplication::init() {
    log::nfo << "uix::CApplication::init()::" << this << log::end;
    onInit();
    return true;
  }
  
  bool CApplication::free() {
    log::nfo << "uix::CApplication::free()::" << this << log::end;
    
    return true;
  }
  
  int CApplication::exec(int nMode/*=0*/) {
    log::nfo << "uix::CApplication::exec()::" << this << log::end;
    
    try {
      
      // @todo: run mLoop.exec()
      // @todo: mLoop stops => CApplication stop  
      
      mRunning = init();
      
      MSG msg;
      while (mRunning) {
        if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
          ::TranslateMessage(&msg);
          ::DispatchMessage(&msg);
          mRunning = msg.message != WM_QUIT;
        } else {
          onTick(::GetTickCount());
        }
      }
      
      mRunning = !free();
      
      return (int)(msg.wParam);
    } catch (...) {
      log::err << "[ERROR] " << log::end;
      return -1;
    }
    
  }
  
  int CApplication::quit(int nCode/*=0*/) {
    log::nfo << "uix::CApplication::quit(int)::" << this << log::end;
    mRunning = false;
    onExit();
    return nCode;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CApplication* CApplication::instance() {
    if (!sInstance) new CApplication;
    // this will be deleted by the CObject::CRegistry
    return sInstance;
  }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CApplication::onInit()    { }
  void CApplication::onTick(long) { }
  void CApplication::onExit()    { }
}}
