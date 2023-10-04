#ifndef __cym_capplication_hpp__
#define __cym_capplication_hpp__

#include "cym/cym.hpp"
#include "uix/CApplication.hpp"
#include "cym/TController.hpp"
#include "cym/CScreen.hpp"

namespace cym {
  class CApplication : public uix::CApplication {
      using super = uix::CApplication;
    public:
      CApplication();
      ~CApplication();
    public:
      virtual bool init() override;
      virtual bool tick(float fDelta=0.f) override;
  };
} // namespace cym

#endif //__cym_capplication_hpp__