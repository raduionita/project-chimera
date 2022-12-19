#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "uix/uix.hpp"

namespace uix {
#if defined(PLATFORM_WINDOWS)
#include "win/CApplication.hpp"
  using CApplication = win::CApplication;
#elif defined(PLATFORM_LINUX)
#include "unx/CApplication.hpp"
  using CApplication = unx::CApplication;
#elif defined(PLATFORM_MACOS)
#include "osx/CApplication.hpp"
  using CApplication = osx::CApplication;
#else
#error Unsupported platform!
#endif //PLATFORM_XXXXX
} // namespace uix

#endif //__uix_capplication_hpp__