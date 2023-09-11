#include "sys/CApplication.hpp"

namespace sys {
  const CApplication* CApplication::sInstance{nullptr};

  // ctor
  CApplication::CApplication() {
    // LOGDBG("sys::CApplication::CApplication()");
    sInstance = this;
  }  
  // dtor
  CApplication::~CApplication() {
    // LOGDBG("sys::CApplication::~CApplication()");
  }

  int CApplication::exec() {
    try {
      init();
      // try to loop
      try {
        loop();
      } catch (sys::CException& ex) {
        // TODO
      }
      // cleanup
      free();
      // exit
      quit(0);
      // last inputs
      poll();
      // done
      return 0;
    } catch (sys::CException& e) {
      // TODO: log error
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
    // timers
    auto  tTp1 = std::chrono::steady_clock::now();
    auto  tTp2 = std::chrono::steady_clock::now();
    std::chrono::duration<float> tElp;
    float fElapsed = 0.f; 
    while (mRunning) {
      tTp2 = std::chrono::steady_clock::now();
      tElp = tTp2 - tTp1;
      tTp1 = tTp2;
      fElapsed = tElp.count();
      /*mRunning=*/ poll() && tick(fElapsed);
    }
  }

  bool CApplication::tick(float fElapsed) {
    onTick(fElapsed);
    return mRunning;
  }

  void CApplication::quit(int nCode) {
    mRunning = false;
  }

  bool CApplication::poll() {
    return true;
  }

  void CApplication::onInit() { }
  void CApplication::onTick(float fElapsed) { mRunning = false; }
  void CApplication::onFree() { }
} // namespace sys