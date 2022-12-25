#ifndef __uix_cframe_hpp__
#define __uix_cframe_hpp__

#include "uix/uix.hpp"

#ifdef PLATFORM_WINDOWS
#include "win/CFrame.hpp"
namespace uix {
  using CFrame = win::CFrame;
} // namespace uix
#endif // PLATFORM_WINDOWS
#ifdef PLATFORM_LINUX
#include "nix/CFrame.hpp"
namespace uix {
  using CFrame = nix::CFrame;
} // namespace uix
#endif // PLATFORM_LINUX
#ifdef PLATFORM_MACOS
#include "osx/CFrame.hpp"
namespace uix {
  typedef osx::CFrame CFrame;
} // namespace uix
#endif // PLATFORM_MACOS

#endif //__uix_cframe_hpp__