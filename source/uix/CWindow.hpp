#ifndef __uix_cwindow_hpp__
#define __uix_cwindow_hpp__

#include "uix/uix.hpp"

namespace uix {
#if defined(PLATFORM_WINDOWS)
#include "win/CWindow.hpp"
  using CWindow = win::CWindow;
#elif defined(PLATFORM_LINUX)
#include "unx/CWindow.hpp"
  using CWindow = unx::CWindow;
#elif defined(PLATFORM_MACOS)
#include "osx/CWindow.hpp"
  using CWindow = osx::CWindow;
#else
#error Unsupported platform!
#endif //PLATFORM_XXXXX
} // namespace uix

#endif //__uix_cwindow_hpp__