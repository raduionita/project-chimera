#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app/app.hpp"
#include "cym/CApplication.hpp"

namespace app {
  class CApplication : public cym::CApplication { // .. uix::CApplication : sys::CApplication : sys::CExecutable
      using super = cym::CApplication;
    public:
      virtual void onInit() override;
      virtual void onTick(float fDelta) override;
  };
} // namespace app


#endif //__app_capplication_hpp__ 


