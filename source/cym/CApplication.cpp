#include "cym/CApplication.hpp"
// #include "cym/CScreen.hpp"

namespace cym {
  // ctor
  CApplication::CApplication() {
    // LOGDBG("cym::CApplication::CApplication()");
  }
  // dtor
  CApplication::~CApplication() {
    // LOGDBG("cym::CApplication::~CApplication()");
  }

  bool CApplication::init() {
    // LOGDBG("cym::CApplication::init()");
    return uix::CApplication::init();
        // && cym::CScreenManager::bootup();
  }

  bool CApplication::tick(float fElapsed) {
    return uix::CApplication::tick(fElapsed);
        // && cym::CScreenManager::update();
  }
} // namespace cym