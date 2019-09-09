#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#define LOGGING 1

#include "cym/uix/CApplication.hpp"

using namespace cym;
using log = cym::sys::CLogger;

namespace app {
  class CApplication : public uix::CApplication {
    protected:
    void onInit()         override;
    void onTick(long = 0) override;
    void onExit()         override;
  };
}

#endif //__app_capplication_hpp__
