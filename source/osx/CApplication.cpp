#include "osx/CApplication.hpp"

#ifdef PLATFORM_MACOS

namespace osx {
  CApplication::CApplication() {
    LOGDBG("osx::CApplication::CApplication()");
  }

  CApplication::~CApplication() {
    LOGDBG("osx::CApplication::~CApplication()");
  }
} // namespace osx

#endif // PLATFORM_MACOS
