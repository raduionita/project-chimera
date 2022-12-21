#ifndef __uix_capplication_hpp__
#define __uix_capplication_hpp__

#include "uix/uix.hpp"
#include "sys/CApplication.hpp"

namespace {
  class CApplication : public sys::CApplication {
    public:
      // start
      virtual int  exec();
      // init/clean
      virtual bool init();
              bool free();
      // actions
              void loop();
      virtual bool tick(float fElapsed=0.f);
              void quit(int nCode=0);
              bool poll();
      // events
      virtual void onInit();
      virtual void onTick(float=0.f);
      virtual void onFree();
  };
} // namespace


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