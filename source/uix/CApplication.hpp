#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "uix/uix.hpp"

#if defined(PLATFORM_WINDOWS)
#include "win/CApplication.hpp"
namespace uix {
  using CApplication = win::CApplication;
} // namespace uix
#elif defined(PLATFORM_LINUX)
#include "unx/CApplication.hpp"
namespace uix {
  using CApplication = unx::CApplication;
} // namespace uix
#elif defined(PLATFORM_MACOS)
#include "osx/CApplication.hpp"
namespace uix {
  using CApplication = osx::CApplication;
} // namespace uix
#else
#error Unsupported platform!
#endif //PLATFORM_XXXXX


#endif //__uix_capplication_hpp__