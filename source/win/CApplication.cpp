#include "win/CApplication.hpp"

namespace win {
  // ctors
  
  CApplication::CApplication() {

  }

  // actions

  int CApplication::exec() {
    try {
      init();

      try {
        loop();
      } catch (sys::CException& ex) {
        // TODO
      }

      free();

      exit();

      poll();

      return 0;
    } catch (sys::CException& e) {
      // TODO: log error
      return -1;
    }
  }

  bool CApplication::init() {
    onInit();
    return false;
  }

  bool CApplication::free() {
    onFree();
    return false;
  }

  void CApplication::loop() {
    while (mRunning) {
      tick();
    }
  }

  bool CApplication::exit() {
    return false;
  }

  bool CApplication::poll() {
    return false;
  }

  bool CApplication::tick() {
    onTick(0);
  }

  // events

  void CApplication::onInit() { }

  void CApplication::onFree() { }

  void CApplication::onTick(int) { }
} // namespace uix
