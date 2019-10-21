#include "uix/CApplication.hpp"
#include "uix/CConsole.hpp"
#include "uix/CStyle.hpp"

namespace uix {
  CApplication* CApplication::sInstance{nullptr};
  
  CApplication::CApplication(int nCmdShow/*=0*/) : CModule() {
    log::nfo << "uix::CApplication::CApplication()::" << this << log::end;
    assert(!sInstance && "CApplication::sIntastace already defined.");
    sInstance = this;
    mConsole  = new CConsole(this, nCmdShow);
  }
  
  CApplication::~CApplication() {
    log::nfo << "uix::CApplication::~CApplication()::" << this << log::end;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CStyle* CApplication::style() {
    if (!mStyle) {
      log::nfo << "uix::CApplication::style()::" << this << log::end;
      style(new CStyle);
    }
    return mStyle;
  }
  
  bool CApplication::style(CStyle* pStyle) {
    log::nfo << "uix::CApplication::style(CStyle*)::" << this << log::end;
    if (mStyle != nullptr && mStyle != pStyle) {
      DELETE(mStyle);
    }
    return !!(mStyle = pStyle);
  }
  
  bool CApplication::init() {
    log::nfo << "uix::CApplication::init()::" << this << log::end;
  
    if (!CModule::init()) {
      log::nfo << "[CApplication] CModel::init() failed!" << log::end;
      ::MessageBox(NULL, "[CApplication] CModel::init() failed!", "Error", MB_OK);
      return false;
    }
  
    onInit();
    
    return (mRunning = true);
  }
  
  bool CApplication::idle(int nElapsed/*=0*/) {
    // log::nfo << "uix::CApplication::idle("<< nElapsed <<")::" << this << log::end;
    onIdle(nElapsed);
    return true;
  }
  
  bool CApplication::free() {
    log::nfo << "uix::CApplication::free()::" << this << log::end;
    onFree();
    return CModule::free();
  }
  
  bool CApplication::exec(int nMode/*=0*/) {
    log::nfo << "uix::CApplication::exec()::" << this << log::end;
    try {
      init();
      // prepare
      DWORD     nCurTicks{::GetTickCount()};
      // the run loop
      while (mRunning) {
        if (!::HandleMessage()) {
          break;
        }
        mRunning && idle(::GetTickCount() - nCurTicks);
      }
      free();
      return 0;
    } catch (sys::CException& ex) {
      log::err << ex << log::end;
      return -1;
    }
  }
  
  bool CApplication::quit(int nCode/*=0*/) {
    log::nfo << "uix::CApplication::quit(int)::" << this << log::end;
    ::PostQuitMessage(nCode);
    return true;
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CApplication* CApplication::instance() { return (!sInstance) ? sInstance = new CApplication : sInstance; }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CApplication::onInit()    { }
  void CApplication::onIdle(int) { }
  void CApplication::onFree()    { }
}
