#include "sys/CApplication.hpp"

namespace sys {
  const CApplication* CApplication::sInstance{nullptr};

  // ctor
  CApplication::CApplication() {
    LOGDBG("sys::CApplication::CApplication()");
    sInstance = this;
  }  
  // dtor
  CApplication::~CApplication() {
    LOGDBG("sys::CApplication::~CApplication()");
  }

  int CApplication::exec() {
    try {
      init();
      // main loop
      loop();
      // cleanup
      free();
      // exit
      quit(0);
      // last inputs
      poll();
      // done
      return 0;
    } catch (sys::CException& exp) {
      LOGERR("::ERROR::EXEC:" << exp);
      return -1;
    }
  }
  
  bool CApplication::init() {
    onInit();
    return true;
  }
  
  bool CApplication::free() {
    onFree();
    return true;
  }

  void CApplication::loop() {
    // try to loop
    try {
      // timers
      auto  tTp1 = std::chrono::steady_clock::now();
      auto  tTp2 = std::chrono::steady_clock::now();
      std::chrono::duration<float> tElp;
      float fDelta = 0.f; 
      while (mRunning) {
        tTp2 = std::chrono::steady_clock::now();
        tElp = tTp2 - tTp1;
        tTp1 = tTp2;
        fDelta = tElp.count();
        poll();
        tick(fDelta);
      }
    } catch (sys::CException& ex) {
      LOGERR("::ERROR::LOOP:" << ex);
    }
  }

  bool CApplication::tick(float fDelta) {
    onTick(fDelta);
    return true;
  }

  void CApplication::quit(int nCode) {
    mRunning = false;
  }

  bool CApplication::poll() {
    return true;
  }

  void CApplication::onInit() { }
  void CApplication::onTick(float fDelta) { mRunning = false; }
  void CApplication::onFree() { }
} // namespace sys