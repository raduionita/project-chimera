#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app/app.hpp"
#include "sys/CApplication.hpp"

namespace app {
  class CApplication : public sys::CApplication {
    public:
      CApplication();
    public:
      int exec(int argc, char** argv);
  };
} // namespace appto

#endif //__app_capplication_hpp__