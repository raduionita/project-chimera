#ifndef __uix_cconsole_hpp__
#define __uix_cconsole_hpp__

#include "uix/uix.hpp"

#ifdef PLATFORM_WINDOWS
#include "win/CConsole.hpp"
namespace uix {
  using CConsole = win::CConsole;
} // namespace uix
#endif // PLATFORM_WINDOWS
#ifdef PLATFORM_LINUX
#include "nix/CConsole.hpp"
namespace uix {
  using CConsole = nix::CConsole;
} // namespace uix
#endif // PLATFORM_LINUX
#ifdef PLATFORM_MACOS
#include "osx/CConsole.hpp"
namespace uix {
  typedef osx::CConsole CConsole;
} // namespace uix
#endif // PLATFORM_MACOS

#endif //__uix_cconsole_hpp__