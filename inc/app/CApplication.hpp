#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#define LOGGING
#define LOGGING_INFO
#define LOGGING_COUT

#include "cym/uix/CApplication.hpp"
#include "cym/uix/CEvent.hpp"

using namespace cym;
using log = cym::log;

namespace app {
  class CApplication : public uix::CApplication {
    protected:
      uix::CFrame*   mFrame;
      uix::CSurface* mSurface;
    protected:
      void onInit()      override;
      void onTick(int=0) override;
      void onFree()      override;
    protected:
      void onKeydown(uix::CEvent*);
  };
}

#endif //__app_capplication_hpp__
