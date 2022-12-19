#ifndef __uix_cconsole_hpp__
#define __uix_cconsole_hpp__

#include "uix/uix.hpp"

namespace uix {
#if defined(PLATFORM_WINDOWS)
#include "win/CConsole.hpp"
  using CConsole = win::CConsole;
#elif defined(PLATFORM_LINUX)
#include "unx/CConsole.hpp"
  using CConsole = unx::CConsole;
#elif defined(PLATFORM_MACOS)
#include "osx/CConsole.hpp"
  using CConsole = osx::CConsole;
#else
#error Unsupported platform!
#endif //PLATFORM_XXXXX
} // namespace uix

#endif //__uix_cconsole_hpp__