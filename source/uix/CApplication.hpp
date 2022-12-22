#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "uix/uix.hpp"

#ifdef PLATFORM_WINDOWS
#include "win/CApplication.hpp"
namespace uix {
  using CApplication = win::CApplication;
} // namespace uix
#endif // PLATFORM_WINDOWS
#ifdef PLATFORM_LINUX
#include "unx/CApplication.hpp"
namespace uix {
  using CApplication = unx::CApplication;
} // namespace uix
#endif // PLATFORM_LINUX
#ifdef PLATFORM_MACOS
#include "osx/CApplication.hpp"
namespace uix {
  typedef osx::CApplication CApplication;
} // namespace uix
#endif // PLATFORM_MACOS

#endif //__uix_capplication_hpp__