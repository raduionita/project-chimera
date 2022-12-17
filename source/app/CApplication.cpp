#include "app/CApplication.hpp"

namespace app {
  CApplication::CApplication() { }

  void CApplication::onInit() {
    BENTAG("app::CApplication::onInit()");
    LOGTAG("app::CApplication::onInit()");

    LOGDBG("");
  }

  void CApplication::onTick(int) {
    LOGTAG("app::CApplication::onTick()");
    LOGDBG("");

    quit(0);
  }
} // namespace app
