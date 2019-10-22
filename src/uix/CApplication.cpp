#include "uix/CApplication.hpp"
#include "uix/CConsole.hpp"
#include "uix/CStyle.hpp"
#include "uix/CLoop.hpp"

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
    DELETE(mConsole);
    DELETE(mLoop);
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
  
  bool CApplication::tick(int nElapsed/*=0*/) {
    // log::nfo << "uix::CApplication::tick("<< nElapsed <<")::" << this << log::end;
    onTick(nElapsed);
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
      // -> loop
      loop()->exec();
      // <- loop
      free();
      return 0;
    } catch (sys::CException& ex) {
      log::err << ex << log::end;
      return -1;
    }
  }
  
  CLoop* CApplication::loop() {
    log::nfo << "uix::CApplication::loop()::" << this << log::end;
    
    return mLoop ? mLoop : mLoop = new CEventLoop(this);
  }
  
  bool CApplication::quit(int nCode/*=0*/) {
    log::nfo << "uix::CApplication::quit(int)::" << this << log::end;
    ::PostQuitMessage(nCode);
    return true;
  }
  
  bool CApplication::runs() { return mRunning; }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CApplication* CApplication::instance() { return (!sInstance) ? sInstance = new CApplication : sInstance; }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CApplication::onInit()    { }
  void CApplication::onTick(int) { }
  void CApplication::onFree()    { }
}
