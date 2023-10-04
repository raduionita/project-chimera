#ifndef __uix_cwindow_hpp__
#define __uix_cwindow_hpp__

#include "uix/uix.hpp"

#ifdef PLATFORM_WINDOWS
#include "win/CWindow.hpp"
namespace uix {
  using CWindow = win::CWindow;
} // namespace uix
#endif // PLATFORM_WINDOWS
#ifdef PLATFORM_LINUX
#include "nix/CWindow.hpp"
namespace uix {
  using CWindow = nix::CWindow;
} // namespace uix
#endif // PLATFORM_LINUX
#ifdef PLATFORM_MACOS
#include "osx/CWindow.hpp"
namespace uix {
  typedef osx::CWindow CWindow;
} // namespace uix
#endif // PLATFORM_MACOS

#endif //__uix_cwindow_hpp__