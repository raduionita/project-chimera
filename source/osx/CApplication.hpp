#ifndef __osx_capplication_hpp__
#define __osx_capplication_hpp__

#ifdef PLATFORM_MACOS

#include "osx/osx.hpp"
#include "sys/CApplication.hpp"

namespace osx {
  class CApplication : public sys::CApplication {
      using super = sys::CApplication;
    public:
      CApplication();
      ~CApplication();
  };
} // namespace osx

#endif // PLATFORM_MACOS

#endif //__osx_capplication_hpp__