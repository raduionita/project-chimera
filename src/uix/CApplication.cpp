#include "uix/CApplication.hpp"
#include "uix/CStyle.hpp"

namespace uix {
  CApplication* CApplication::sInstance{nullptr};
  
  CApplication::CApplication(int nCmdShow/*=0*/) : CModule() {
    CYM_LOG_NFO("uix::CApplication::CApplication()::" << this);
    assert(!sInstance && "CApplication::sIntastace already defined.");
    sInstance = this;
    
    mConsole  = new CConsole(this, nCmdShow);
    mLoop     = new CEventLoop();
  }
  
  CApplication::~CApplication() {
    CYM_LOG_NFO("uix::CApplication::~CApplication()::" << this);
    // DELETE(mConsole);
    // DELETE(mLoop);
  }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  CStyle* CApplication::style() {
    if (!mStyle) {
      CYM_LOG_NFO("uix::CApplication::style()::" << this);
      style(new CStyle);
    }
    return mStyle;
  }
  
  bool CApplication::style(CStyle* pStyle) {
    CYM_LOG_NFO("uix::CApplication::style(CStyle*)::" << this);
    if (mStyle != nullptr && mStyle != pStyle) {
      DELETE(mStyle);
    }
    return !!(mStyle = pStyle);
  }
  
  bool CApplication::init() {
    CYM_LOG_NFO("uix::CApplication::init()::" << this);
  
    if (!CModule::init()) {
      CYM_LOG_NFO("[CApplication] CModel::init() failed!");
      ::MessageBox(NULL, "[CApplication] CModel::init() failed!", "Error", MB_OK);
      return false;
    }
  
    onInit();
    
    return (mRunning = true);
  }
  
  bool CApplication::tick(float fElapsed/*=0*/) {
    // CYM_LOG_NFO("uix::CApplication::tick("<< fElapsed <<")::" << this);
    onTick(fElapsed);
    return true;
  }
  
  bool CApplication::free() {
    CYM_LOG_NFO("uix::CApplication::free()::" << this);
    onFree();
    return CModule::free();
  }
  
  bool CApplication::poll() {
    MSG msg;
    return TRUE == ::HandleMessage(&msg);
  }
  
  int  CApplication::load() {
    CYM_LOG_NFO("uix::CApplication::load()::" << this);
    try {
      CYM_LOG_NFO("uix::CApplication::load()::init");
      init();
      
      CYM_LOG_NFO("uix::CApplication::load()::exec");
      try { exec(); } catch (sys::exception& ex) { CYM_LOG_ERR("EXEC exception! " << ex); } 
      
      CYM_LOG_NFO("uix::CApplication::load()::free");
      free();
      
      CYM_LOG_NFO("uix::CApplication::load()::exit");
      exit();
      
      CYM_LOG_NFO("uix::CApplication::load()::poll");
      poll();
    
      return 0;
    } catch (sys::exception& ex) {
      CYM_LOG_ERR("LOAD exception! " << ex);
      return -1;
    }
  }
  
  void CApplication::exec() {
    CYM_LOG_NFO("uix::CApplication::exec()::" << this);
    // -> loop
    loop();
  }
  
  void CApplication::loop() {
    CYM_LOG_NFO("uix::CApplication::loop()::" << this);
    if (mLoop)
      mLoop->loop();
    else
      while (runs())
        tick(::GetTickElapsed()/1000.f) && poll();
  }
  
  bool CApplication::quit(int nCode/*=0*/) {
    CYM_LOG_NFO("uix::CApplication::quit(int)::" << this);
    mRunning = false;
    return true;
  }
  
  bool CApplication::exit(int nCode/*=0*/) {
    CYM_LOG_NFO("uix::CApplication::exit(int)::" << this);
    ::PostQuitMessage(nCode);
    return true;
  }
  
  bool CApplication::runs() const        { return mRunning; }
  
  void CApplication::runs(bool bRunning) { mRunning = bRunning; }
  
  bool CApplication::isRunning() const { return mRunning; }
  
  void CApplication::isRunning(bool bRunning) { mRunning = bRunning; }
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  CApplication* CApplication::instance() { return (!sInstance) ? sInstance = new CApplication : sInstance; }
    
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  void CApplication::onInit()    { }
  void CApplication::onTick(int) { }
  void CApplication::onFree()    { }
}
