#ifndef __app_capplication_hpp__
#define __app_capplication_hpp__

#include "app/app.hpp"
#include "cym/CApplication.hpp"

namespace app {
  class CApplication : public cym::CApplication {
    public:
      CApplication();
      ~CApplication();
    public:
      virtual void onInit() override;
      virtual void onTick(float=0.f) override;
  };
} // namespace appto

#endif //__app_capplication_hpp__