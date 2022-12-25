#ifndef __osx_cwindow_hpp__
#define __osx_cwindow_hpp__

#ifdef PLATFORM_MACOS

#include "osx/osx.hpp"
#include "sys/CLogger.hpp"

namespace osx {
  class CWindow {
    public:
      virtual ~CWindow() = default;
  };
} // namespace osx

#endif // PLATFORM_MACOS

#endif //__osx_cwindow_hpp__