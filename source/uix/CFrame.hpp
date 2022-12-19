#ifndef __uix_cframe_hpp__
#define __uix_cframe_hpp__

#include "uix/uix.hpp"

namespace uix {
#if defined(PLATFORM_WINDOWS)
#include "win/CFrame.hpp"
  using CFrame = win::CFrame;
#elif defined(PLATFORM_LINUX)
#include "unx/CFrame.hpp"
  using CFrame = unx::CFrame;
#elif defined(PLATFORM_MACOS)
#include "osx/CFrame.hpp"
  using CFrame = osx::CFrame;
#else
#error Unsupported platform!
#endif //PLATFORM_XXXXX
} // namespace uix

#endif //__uix_cframe_hpp__